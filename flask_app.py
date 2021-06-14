# A very simple Flask Hello World app for you to get started with...

from flask import Flask,request

app = Flask(__name__)

data1="zero"
data2="no gas detected"

@app.route('/')
def hello_world():
    website = '''
<!DOCTYPE html>
<html>
<body>
    <h1>to get gas sensor readings</h1>
    <ul>
        <li><a href="/gas">gas sensor</a></li>
    </ul>
     <h1>to get motion sensor readings</h1>
    <ul>
        <li><a href="/motion">motion sensor</a></li>
    </ul>
</body>
</html>'''
    return website

@app.route('/motion', methods=["POST","GET"])
def hello():
    global data1
    if(request.method=="POST"):
        data1=request.data
    return "there are " + str(data1) + " motions detected "

@app.route('/gas', methods=["POST","GET"])
def hello1():
    global data2
    if(request.method=="POST"):
        data2=request.data
    return "gas sensor value is : " +  str(data2)



