from django.contrib import admin

# Register your models here.

from .models import Admin, Courses

admin.site.register(Admin)
admin.site.register(Courses)
