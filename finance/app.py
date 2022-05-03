import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date

from helpers import apology, login_required, lookup, usd

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
# if not os.environ.get("API_KEY"):
#     raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    try:
        rows = db.execute(
            "SELECT * FROM purchases WHERE user_id = ?", int(session["user_id"]))
        return render_template("index.html", rows=rows)

    except:
        return apology("Unable to load recent purchases")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Please input a ticker symbol")
        elif not request.form.get("shares"):
            return apology("Please input numbers of shares to buy")

        # Check if the symbol inputted is valid and then proceed
        symbol_lookup = lookup(request.form.get("symbol"))
        if symbol_lookup == None:
            return apology("Incorrect ticker symbol")
        shares = request.form.get("shares")
        total_amount = symbol_lookup["price"] * int(shares)
        time = date.today().strftime("%d/%m/%Y")
        cash_left = db.execute(
            "SELECT cash FROM users WHERE id = ?", int(session["user_id"]))

        if len(cash_left) == 1:
            cash_left = cash_left[0]["cash"]
            if total_amount <= cash_left:
                cash_left = cash_left - total_amount
                cash_left = "{:.2f}".format(cash_left)
                db.execute("UPDATE users SET cash = ? WHERE id = ?",
                           cash_left, int(session["user_id"]))
                db.execute(
                    "INSERT INTO purchases (user_id, shares, symbol, price_purchased, cash_left, time_purchased) VALUES (?, ?, ?, ?, ?, ?)", int(session["user_id"]), shares, symbol_lookup["symbol"], total_amount, cash_left, time)
                return render_template("inquiry.html", symbol_lookup=symbol_lookup, shares=shares, total_amount=total_amount,
                                       cash_left=cash_left, time=time)
            else:
                return apology("Insufficient funds")

    return render_template("buy.html")


@ app.route("/history")
@ login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@ app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        username = request.form.get("username")
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@ app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@ app.route("/quote", methods=["GET", "POST"])
@ login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Please input a ticker symbol", 405)
        symbol_lookup = lookup(request.form.get("symbol"))
        if symbol_lookup == None:
            return apology("Incorrect ticker symbol")

        return render_template("quoted.html", symbol_lookup=symbol_lookup)
    else:
        return render_template("quote.html")


@ app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Username missing", 403)
        elif not request.form.get("password"):
            return apology("Missing password", 403)
        elif not request.form.get("confirmation") or (request.form.get("password") != request.form.get("confirmation")):
            return apology("Passwords not matching", 403)

        username = request.form.get("username")
        password = request.form.get("password")

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                   username, generate_password_hash(password))
        return redirect("/")

    return render_template("register.html")


@ app.route("/sell", methods=["GET", "POST"])
@ login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
