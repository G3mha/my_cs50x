import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


# sql cmd

# CREATE TABLE history (
# transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
# symbol TEXT NOT NULL,
# name TEXT NOT NULL, ### added afterwards
# quote INTEGER NOT NULL,
# shares INTEGER NOT NULL,
# total INTEGER NOT NULL,
# time DATETIME NOT NULL,
# u_id INTEGER NOT NULL,
# FOREIGN KEY(u_id) REFERENCES users(id));

# ENTER IN finance.db IN ONE LINE
# CREATE TABLE history (transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, symbol TEXT NOT NULL, quote INTEGER NOT NULL, shares INTEGER NOT NULL, total INTEGER NOT NULL, time DATETIME NOT NULL, u_id INTEGER NOT NULL, FOREIGN KEY(u_id) REFERENCES users(id));

# in case of rename
# ALTER TABLE hitsory
# RENAME TO history

# in case of
# ALTER TABLE table_name
# ADD column_name datatype;

    # RESULT

    # CREATE TABLE users (
    # id INTEGER,
    # username TEXT NOT NULL,
    # hash TEXT NOT NULL,
    # cash NUMERIC NOT NULL DEFAULT 10000.00,
    # PRIMARY KEY(id)
    # );

    # CREATE TABLE history (
    # transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    # symbol TEXT NOT NULL,
    # name TEXT NOT NULL, ### added afterwards
    # quote INTEGER NOT NULL,
    # shares INTEGER NOT NULL,
    # total INTEGER NOT NULL,
    # time DATETIME NOT NULL,
    # u_id INTEGER NOT NULL,
    # FOREIGN KEY(u_id) REFERENCES users(id)
    # );

    # CREATE UNIQUE INDEX username ON users (username);
    # CREATE TABLE sqlite_sequence(name,seq);



@app.route('/')
@login_required
def index():
    '''Show portfolio of stocks'''
    portfolio = db.execute('select symbol as symbol, sum(shares) as shares from history where u_id = (?) group by symbol', session['user_id'])
    stocks, assets = [], 0
    for row in portfolio:
        stock = lookup(row.get('symbol'))
        quote = stock.get('price')
        row['name'] = stock.get('name')
        if (row.get('shares') == 0):
            continue
        shares = row.get('shares')
        total = shares * quote
        row['quote'] = usd(quote)
        row['total'] = usd(total)
        row['change'] = round(shares * stock.get('price'), 2)
        row['changepc'] = round(100 * stock.get('price'), 2)
        assets += round(total, 2)
        if shares != 0:
            stocks.append(row)
    cash = db.execute('select cash from users where id = (?)', session['user_id'])
    balance, equity = cash[0]['cash'], assets
    assets += balance
    return render_template('index.html', stocks=stocks, equity=usd(equity), balance=usd(balance), assets=usd(assets))


@app.route('/buy', methods=['GET', 'POST'])
@login_required
def buy():
    '''Buy shares of stock'''
    if request.method == 'GET':
        return render_template('buy.html')
    if not request.form.get('symbol'):
        return apology('must provide symbol')
    elif lookup(request.form.get('symbol')) == None:
        return apology('stock not found')
    if request.form.get('shares') == None:
        return apology('must provide number of shares')
    stock_temp = request.form.get('symbol')
    stock_temp = stock_temp.upper()
    stock = lookup(stock_temp); shares = request.form.get('shares')
    if not(shares.isdigit()):
        return apology('shares should be a whole number')
    elif not(int(shares) > 0):
        return apology('buy at least one share')
    shares = int(shares); quote = stock.get('price')
    cash = db.execute('SELECT cash FROM users WHERE id = (?)', session['user_id'])
    balance, time, total = cash[0]['cash'], datetime.now(), shares * quote
    if balance < total:
        return apology('not enough energy')
    balance -= total
    balance = round(balance, 2)
    symbol = stock.get('symbol'); name = stock.get('name')
    db.execute('INSERT INTO history (symbol, name, quote, shares, total, time, u_id) VALUES(?, ?, ?, ?, ?, ?, ?)', symbol, name, quote, shares, total, time, session['user_id'])
    db.execute('UPDATE users SET cash = (?) WHERE id = (?)', balance, session['user_id'])
    flash('({}) Successfully bought {} shares of {} at a price of {}\nCurrent balance: {}'.format(time, shares, symbol, quote, balance))
    return redirect('/')


@app.route('/history')
@login_required
def history():
    '''Show history of transactions'''
    return render_template('history.html', db.execute('SELECT symbol AS Symbol, name AS name, shares AS Shares, quote AS Quote, time AS Time FROM history WHERE u_id = (?)', session['user_id']))


@app.route('/login', methods=['GET', 'POST'])
def login():
    '''Log user in'''
    session.clear()
    if request.method == 'POST':
        if not(request.form.get('username')):
            return apology('must provide username', 403)
        if not(request.form.get('password')):
            return apology('must provide password', 403)
        rows = db.execute('SELECT * FROM users WHERE username = ?', request.form.get('username'))
        if len(rows) != 1 or not(check_password_hash(rows[0]['hash'], request.form.get('password'))):
            return apology('invalid username and/or password', 403)
        session['user_id'] = rows[0]['id']; return redirect('/')
    return render_template('login.html')


@app.route('/logout')
def logout():
    '''Log user out'''
    session.clear(); return redirect('/')


@app.route('/quote', methods=['GET', 'POST'])
@login_required
def quote():
    '''Get stock quote.'''
    if request.method == 'GET':
        return render_template('quote.html')
    stock = lookup(request.form.get('symbol'))
    if stock == None:
        return apology('invalid symbol')
    name, quote, symbol = stock.get('name'), stock.get('price'), stock.get('symbol')
    return render_template('quoted.html', name=name, quote=usd(quote), symbol=symbol)


@app.route('/register', methods=['GET', 'POST'])
def register():
    '''Register user'''
    if not(request.method == 'POST'):
        return render_template('register.html')
    if not(request.form.get('password')) or not(request.form.get('username')):
        return apology('bad information input')
    if request.form.get('confirmation') != request.form.get('password'):
        return apology('password confirmation does not match')
    if len(db.execute('SELECT * FROM users WHERE username = (?)', request.form.get('username'))) == 0:
        username, password = request.form.get('username'), request.form.get('password')
        password_hash = generate_password_hash(password); db.execute('INSERT INTO users (username, hash) VALUES(?, ?)', username, password_hash)
        rows = db.execute('SELECT * FROM users WHERE username = (?)', username); session['user_id'] = rows[0]['id']
        flash('Registered successfully!'); return redirect('/')
    return apology('username already taken')


@app.route('/sell', methods=['GET', 'POST'])
@login_required
def sell():
    '''Sell shares of stock'''
    if request.method == 'GET':
        stocks, portfolio = [], db.execute('select symbol as symbol, sum(shares) as shares from history where u_id = (?) group by symbol', session['user_id'])
        for stock in portfolio:
            stocks.append(stock.get('symbol'))
        return render_template('sell.html', stocks=stocks)
    if not request.form.get('shares'):
        return apology('shares unstated')
    shares_tosell, stock_tosell = request.form.get('shares'), request.form.get('symbol')
    shares_current = db.execute('select sum(shares) as shares from history where symbol = (?) and u_id = (?)', stock_tosell, session['user_id']); shares_current = int(shares_current[0]['shares'])
    if not shares_tosell.isdigit() or int(shares_tosell) < 1:
        return apology('incorrect shares format')
    elif int(shares_tosell) > shares_current:
        return apology('selling more than is owned')
    shares_tosell = int(shares_tosell)
    cash = db.execute('select cash from users where id = (?)', session['user_id']); balance = cash[0]['cash']
    stock_current = lookup(stock_tosell); quote = stock_current.get('price')
    total = shares_tosell * quote; balance += total
    time, shares_tosell = datetime.now(), 0 - shares_tosell
    balance = round(balance, 2)
    db.execute('update users set cash = (?) where id = (?)', balance, session['user_id']); db.execute('insert into history (symbol, quote, shares, total, time, u_id) values(?, ?, ?, ?, ?, ?)', stock_tosell, quote, shares_tosell, total, time, session['user_id'])
    flash(f'({time}) Successfully sold {(-shares_tosell)} shares of {stock_tosell} at a price of {quote}\nCurrent balance: {balance}'); return redirect('/')