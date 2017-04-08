from django.db import models

class Admin(models.Model):
	admin_username = models.CharField(max_length=50)
	admin_password = models.CharField(max_length=20)
	def __str__(self):
		return self.admin_username

class Instructor(models.Model):
	instructor_email = models.CharField(max_length=100)
	instructor_password = models.CharField(max_length=20)
	def __str__(self):
		return self.instructor_email

class Student(models.Model):
	roll_number = models.CharField(max_length=9)
	student_name = models.CharField(max_length=50)
	def __str__(self):
		return self.roll_number

class Courses(models.Model):
	course_code = models.CharField(max_length=5)
	course_name = models.CharField(max_length=200)
	course_year = models.PositiveIntegerField(default=2016)
	course_sem = models.PositiveIntegerField(default=1)
	enrolled_students = models.ManyToManyField(Student, blank=True)
	course_instructors = models.ManyToManyField(Instructor, blank=True)
	def __str__(self):
		return str(self.course_year) + "-" + str(self.course_sem) + "-" + self.course_code

class Deadline(models.Model):
	deadline_course = models.ForeignKey(Courses, on_delete=models.CASCADE, null=True, blank=True)
	deadline_name = models.CharField(max_length=100)
	deadline_datetime = models.DateTimeField('deadline_datetime')
	def __str__(self):
		return str(self.deadline_course.course_year) + "-" + str(self.deadline_course.course_sem) + "-" + self.deadline_course.course_code + " " + self.deadline_name

class Question(models.Model):
	question_name = models.CharField(max_length=500)
	def __str__(self):
		return self.question_name	

class Answers(models.Model):
	answer_question = models.ForeignKey(Question, null=True, blank=True)
	answer_value = models.PositiveIntegerField()
	answer_student = models.ForeignKey(Student, null=True, blank=True)
	def __str__(self):
		return self.answer_student.roll_number + " " + str(self.answer_value)

class FeedbackForm(models.Model):
	# feedback_course = models.ForeignKey(Courses, on_delete=models.CASCADE, null=True, blank=True)
	feedback_deadline = models.ForeignKey(Deadline, on_delete=models.CASCADE, null=True, blank=True)
	feedback_name = models.CharField(max_length=100)
	feedback_questions = models.ManyToManyField(Question)
	def __str__(self):
		return str(self.feedback_deadline.deadline_course.course_year) + "-" + str(self.feedback_deadline.deadline_course.course_sem) + "-" + self.feedback_deadline.deadline_course.course_code + " " + self.feedback_name