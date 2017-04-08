from django.db import models

from django.contrib.auth.models import User

class Instructor(models.Model):
	user = models.OneToOneField(User, on_delete=models.CASCADE, null=True, blank=True)
	user_type = models.CharField(max_length=10, default="Instructor")
	def __str__(self):
		return self.user.username

class Student(models.Model):
	roll_number = models.CharField(max_length=9)
	student_name = models.CharField(max_length=50)
	user = models.OneToOneField(User, on_delete=models.CASCADE, null=True, blank=True)
	user_type = models.CharField(max_length=10, default="Student")
	def __str__(self):
		return self.roll_number

class Deadline(models.Model):
	deadline_name = models.CharField(max_length=100)
	deadline_datetime = models.DateTimeField('deadline_datetime')
	def __str__(self):
		return self.deadline_name	

class Answers(models.Model):
	answer_value = models.PositiveIntegerField()
	def __str__(self):
		return str(self.answer_value)

class Question(models.Model):
	question_name = models.CharField(max_length=500)
	question_answers = models.ManyToManyField(Answers,blank=True)
	question_id = models.CharField(max_length=200,null=True)
	def __str__(self):
		return self.question_name

class response(models.Model):
	response1=models.PositiveIntegerField()
	response2=models.PositiveIntegerField()
	response3=models.PositiveIntegerField()
	response4=models.PositiveIntegerField()
	response5=models.PositiveIntegerField()

class FeedbackForm(models.Model):
	feedback_deadline = models.OneToOneField(Deadline, on_delete=models.CASCADE, null=True, blank=True)
	feedback_name = models.CharField(max_length=100)
	feedback_questions = models.ManyToManyField(Question)
	feedback_id = models.CharField(max_length=200,null=True)
	def __str__(self):
		return self.feedback_name

class Courses(models.Model):
	course_code = models.CharField(max_length=5)
	course_name = models.CharField(max_length=200)
	course_year = models.PositiveIntegerField(default=2016)
	course_sem = models.PositiveIntegerField(default=1)
	enrolled_students = models.ManyToManyField(Student, blank=True)
	feedback_forms = models.ManyToManyField(FeedbackForm, blank=True)
	assignment_deadline = models.ManyToManyField(Deadline, blank=True)
	def __str__(self):
		return str(self.course_year) + "-" + str(self.course_sem) + "-" + self.course_code