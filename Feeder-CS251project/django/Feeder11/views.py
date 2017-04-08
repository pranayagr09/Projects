from django.shortcuts import render
from django.shortcuts import redirect
import matplotlib.pyplot as plt
# Create your views here.
from django.http import HttpResponse
from django.contrib.auth import authenticate
from django.contrib.auth import login 
from django.contrib.auth.models import User
from django.contrib.auth import logout
from django.shortcuts import render
from django.template import Context
from Feeder11 import models 
import csv
from Feeder11.models import *
from django.contrib import messages
# import pandas as pd
# from Feeder11.models import deadline 
from pylab import *

# Create your views here.
import datetime
from django.http import HttpResponse
from django.views.decorators.cache import cache_control
import json
try:
    import django.utils.simplejson
except:
    import json as simplejson
from django.views.decorators.csrf import csrf_exempt
import urllib.request
import matplotlib.pyplot as plt

def index(request):
    return redirect('Login')

from pylab import figure, axes, pie, title
from matplotlib.backends.backend_agg import FigureCanvasAgg

def see(request):
	if request.user.is_authenticated():
		u=request.user
		if u.is_superuser:
			return redirect('Login')
		else:
			return redirect('InsLogin')
	else:
		username2 = request.POST.get('username', '')
		password2 = request.POST.get('password', '')
		user = authenticate(username=username2, password=password2)
		if user is not None:
			if user.is_superuser :
				login(request,user)
				return redirect('adminPage')
		else:
			user1=authenticate(username="I"+username2,password=password2)
			if user1 is not None:
				login(request,user1)
				return redirect('insPage')
			else:
				messages.add_message(request,messages.INFO,'Bad username or password')
				return redirect('InsLogin')
			
def Login(request):
	if request.user.is_authenticated():
		u=request.user
		if u.is_superuser:
			return redirect('adminPage')
		else :
			return redirect('insPage')
	return render(request,'login.html')

def InsLogin(request):
	if request.user.is_authenticated():
		u=request.user
		if u.is_superuser:
			return redirect('adminPage')
		else:
			return redirect('insPage')
	return render(request,'ins_login.html')

def adminPage(request):
	if request.user.is_authenticated():
		u=request.user
		if u.is_superuser:
			courses = Courses.objects.all()
			student = Student.objects.all()
			return render(request, 'admin-page.html', {'courses': courses, 'student': student})
	else:
		return redirect('Login')

def insPage(request):
	if request.user.is_authenticated():
		u=request.user
		if u.is_superuser:
			courses = Courses.objects.all()
			student = Student.objects.all()
			return render(request, 'admin-page.html', {'courses': courses, 'student': student})
		else:
			courses = Courses.objects.all()
			student = Student.objects.all()
			today = datetime.datetime.now()
			return render(request,'Ins_page.html',{'courses': courses, 'student': student, 'today':today})
	return redirect('InsLogin')

def logout_view(request):
	logout(request)
	return redirect('Login')

def logout_ins(request):
	logout(request)
	return redirect('InsLogin')

def courseadd(request):
	coursename = request.POST['coursename']
	coursecode = request.POST['coursecode']
	year = request.POST['year']
	sem = request.POST['sem']
	midsemdate = request.POST['midsemdate']
	midsemtime = request.POST['midsemtime']
	endsemdate = request.POST['endsemdate']
	endsemtime = request.POST['endsemtime']
	midsem=midsemdate+" "+midsemtime
	endsem=endsemdate+" "+endsemtime
	semno = 0
	add = request.POST.get('add', True)

	if (sem == '1'):
		semno = 1
	if (sem == '2'):
		semno = 2
	if(sem == '3'):
		semno = 3
	coursekey = str(year) + "-" + str(sem) + "-" + coursecode

	c = Courses(course_name = coursename, course_code = coursecode, course_year = year, course_sem = semno)
	c.save()
	d1 = Deadline(deadline_name = "Midsem Exam", deadline_datetime=datetime.datetime.strptime(midsem, "%Y-%m-%d %H:%M"))
	d1.save()
	d2 = Deadline(deadline_name = "Endsem Exam", deadline_datetime=datetime.datetime.strptime(endsem, "%Y-%m-%d %H:%M"))
	d2.save()
	d3 = Deadline(deadline_name = "Midsem Feedback Deadline", deadline_datetime=datetime.datetime.strptime(midsem, "%Y-%m-%d %H:%M"))
	d3.save()
	d4 = Deadline(deadline_name = "Endsem Feedback Deadline", deadline_datetime=datetime.datetime.strptime(endsem, "%Y-%m-%d %H:%M"))
	d4.save()
	c.assignment_deadline.add(d1,d2)
	c.save()
	f1_id=coursekey+"Midsem Feedback Form"
	f1_id=f1_id.replace(" ", "")
	f1 = FeedbackForm(feedback_name ="Midsem Feedback Form",feedback_deadline=d3,feedback_id=f1_id)
	f1.save()
	f2_id=coursekey+"Endsem Feedback Form"
	f2_id=f2_id.replace(" ", "")
	f2 = FeedbackForm(feedback_name ="Endsem Feedback Form",feedback_deadline=d4,feedback_id=f2_id)
	f2.save()
	s="How do you rate this course?"
	s_id=f1_id.replace(" ","")+s.replace(" ", "")
	s1="How do you rate the Professor?"
	s1_id=f1_id.replace(" ","")+s1.replace(" ", "")
	q1 = Question(question_name=s,question_id=s_id)
	q2 = Question(question_name=s1,question_id=s1_id)
	q1.save()
	q2.save()
	f1.feedback_questions.add(q1,q2)
	f1.save()
	s2="How do you rate this course?"
	s2_id=f2_id.replace(" ","")+s2.replace(" ", "")
	s3="How do you rate the Professor?"
	s3_id=f2_id.replace(" ","")+s3.replace(" ", "")
	q3 = Question(question_name=s2,question_id=s2_id)
	q4 = Question(question_name=s3,question_id=s3_id)
	q3.save()
	q4.save()
	f2.feedback_questions.add(q3,q4)
	f2.save()
	c.feedback_forms.add(f1,f2)
	c.save()
	return redirect('adminPage')

def data_reload():
	with open('Feeder11/students_data.csv') as file:
		reader = csv.reader(file)
		for row in reader:
			user=User.objects.filter(username=row[0])
			if not user:	
				_, created = Student.objects.get_or_create(
					roll_number=row[0],
					user = User.objects.create_user(row[0], row[2], row[3]),
					student_name=row[1],
				)

def update(request):
	data_reload()
	return redirect('adminPage')

def addStudent(request):
	class_students = request.POST.getlist('student')
	coursekey = request.POST['add']
	key = coursekey.split("-")
	year = key[0]
	sem = key[1]
	code = key[2]
	course = Courses.objects.get(course_sem=sem, course_year=year, course_code=code)
	for student in class_students:
		course.enrolled_students.add(Student.objects.get(roll_number = student))
	return redirect('adminPage')

def addDeadline(request):
	assignment_name = request.POST['deadlinename']
	assignment_time = request.POST['deadlinedate']+" "+request.POST['deadlinetime']
	coursekey = request.POST['addDeadlineButton']
	key = coursekey.split("-")
	year = key[0]
	sem = key[1]
	code = key[2]
	d1 = Deadline(deadline_name = assignment_name, deadline_datetime=datetime.datetime.strptime(assignment_time, "%Y-%m-%d %H:%M"))
	d1.save()
	c = Courses.objects.get(course_sem=sem, course_year=year, course_code=code)
	c.assignment_deadline.add(d1)
	c.save()
	return redirect('insPage')

def addFeedback(request):
	feedback_name = request.POST['feedbackname']
	feedback_time = request.POST['feedbackdeadlinedate']+" "+request.POST['feedbackdeadlinetime']
	coursekey = request.POST['addFeedbackButton']
	key = coursekey.split("-")
	year = key[0]
	sem = key[1]
	code = key[2]
	d1 = Deadline(deadline_name = feedback_name, deadline_datetime=datetime.datetime.strptime(feedback_time, "%Y-%m-%d %H:%M"))
	d1.save()
	f1_id=coursekey+feedback_name
	f1_id=f1_id.replace(" ", "")
	f1 = FeedbackForm(feedback_name = feedback_name,feedback_deadline=d1)
	num = request.POST['num_ques']
	f1.save()
	for i in range(1,int(float(num))+1):
		s='textquestion'+str(i)
		q=request.POST[s];
		print(q);
		q1=Question(question_name=q,question_id=f1_id+q)
		q1.save()
		f1.feedback_questions.add(q1)
	f1.save()
	c = Courses.objects.get(course_sem=sem, course_year=year, course_code=code)
	c.feedback_forms.add(f1)
	c.save()
	return redirect('insPage')

def signup(request):
	# if request.user.is_authenticated():
	# 	u=request.user
	# 	if u.is_superuser:
	# 		return redirect('adminPage')
	return render(request,'signup.html')

def register(request):
	username=request.POST['username']
	email=request.POST['email']
	password=request.POST['password']
	if username == '' :
		messages.add_message(request,messages.ERROR,'Username can`t be empty')
		return redirect('signup')
	if password == '' :
		messages.add_message(request,messages.ERROR,'Password can`t be empty')
		return redirect('signup')
	if email == '' :
		messages.add_message(request,messages.ERROR,'Email can`t be empty')
		return redirect('signup')
	u=User.objects.filter(username="I"+username)
	if not u:
		newuser=User.objects.create_user("I"+username,email,password)
		newuser.save()
		newins=Instructor.objects.create(user=newuser)
		newins.save()
		messages.add_message(request,messages.ERROR,'Succesfully Registered')
		return redirect('signup')
	else:
		messages.add_message(request,messages.ERROR,'Username already exists')
		return redirect('signup')

def facebook(request):
	if request.method == 'POST':
		access=request.POST['fbuser']
		s="https://graph.facebook.com/v2.8/me?access_token="+access+"&fields=id,email"
		token=urllib.request.urlopen(s)
		data=token.read()
		data=data.decode("utf-8")
		data = json.loads(data)
		u=User.objects.filter(username="I"+data['email'])
		if not u:
			newuser=User.objects.create_user("I"+data['email'],data['email'])
			newuser.save()
			newins=Instructor.objects.create(user=newuser)
			newins.save()
			login(request,newuser)
			return redirect('insPage')
		else:
			u=User.objects.get(username="I"+data['email'])
			login(request,u)
			return redirect('insPage')

def viewFeedback(request,id):
	feedback_form=FeedbackForm.objects.get(pk=id)
	return render(request,'viewFeedback.html',{'feedback_form':feedback_form})

def viewGraph(request,ques):
	matplotlib.use('Agg')
	q=Question.objects.get(pk=ques)
	f = figure(figsize=(6,6))
	colors = ["#E13F29", "#D69A80", "#D63B59", "#AE5552", "#CB5C3B"]
	number=[0,0,0,0,0]
	value=[1,2,3,4,5]
	for a in q.question_answers.all():
		number[a.answer_value-1]=number[a.answer_value-1]+1
	pie(number,labels=value,shadow=False,colors=colors,startangle=90,autopct='%1.1f%%',)
	title(ques, bbox={'facecolor':'0.8', 'pad':5})
	canvas = FigureCanvasAgg(f)
	matplotlib.pyplot.close(f)
	response = HttpResponse(content_type ='image/png')
	canvas.print_png(response)
	return response

def viewAg(request,ques):
	q=Question.objects.get(pk=ques)
	answers=[0,0,0,0,0]
	for a in q.question_answers.all():
		answers[a.answer_value-1]=answers[a.answer_value-1]+1
	r=response(response1=answers[0],response2=answers[1],response3=answers[2],response4=answers[3],response5=answers[4])
	return render(request,'viewAg.html',{'r':r},{'q':q})

@csrf_exempt
def app_login(request):
	if request.method == 'POST':
		# print(request)
		# body = json.loads(request.body.decode("utf-8"))
		# print(body)
		body_unicode = request.body.decode("utf-8")
		# print(body_unicode)
		data = json.loads(str(body_unicode))
		username2 = data['username']
		password2 = data['password']
		user = authenticate(username=username2, password=password2)
		s = False
		if user is not None:
			s = True
			stud= Student.objects.get(roll_number = username2)
			course_query=stud.courses_set.all()
			s="{\"courses\":[";
			for c in course_query:
				feed_list=c.feedback_forms.all()
				ass_list=c.assignment_deadline.all()
				s=s+"{\"course_code\":\""+str(c.course_code)+"\","
				# s=s+"\"course_name\":\""+str(c.course_name)+"\","
				# s=s+"\"course_year\":\""+str(c.course_year)+"\","
				# s=s+"\"course_sem\":\""+str(c.course_sem)+"\","
				s=s+"\"feedback_forms\":["
				for f in feed_list:
					qn_list=f.feedback_questions.all()
					s=s+"{\"feedback_deadline_datetime\":\""+str(f.feedback_deadline.deadline_datetime)+"\","
					s=s+"\"feedback_name\":\""+str(f.feedback_name)+"\","
					s=s+"\"feedback_questions\":["
					for q in qn_list :
						s=s+"{\"question_name\":\""+str(q.question_name)+"\""
						s=s+"},"
					if qn_list:
						s=s[:-1]
					s=s+"]"
					s=s+"},"
				if feed_list:
					s=s[:-1]
				s=s+"]"
				s=s+","
				s=s+"\"assignment_deadline\":["
				for a in ass_list:
					s=s+"{\"deadline_name\":\""+str(a.deadline_name)+"\","
					s=s+"\"deadline_datetime\":\""+str(a.deadline_datetime)+"\","
					s=s[:-1]
					s=s+"},"
				s=s[:-1]
				s=s+"]"
				s=s+"},"
			if course_query:
				s=s[:-1]
			s=s+"]}"
		else:
			s = False
		return HttpResponse(s,content_type="application/json")

