from django.contrib import admin

# Register your models here.

from .models import Student, Instructor, Courses, Question, Courses, Deadline, Answers, FeedbackForm

admin.site.register(Student)
admin.site.register(Instructor)
admin.site.register(Courses)
admin.site.register(Question)
admin.site.register(Deadline)
admin.site.register(Answers)
admin.site.register(FeedbackForm)