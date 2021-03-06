# -*- coding: utf-8 -*-
# Generated by Django 1.10.2 on 2016-10-30 12:50
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Admin',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('admin_username', models.CharField(max_length=50)),
                ('admin_password', models.CharField(max_length=20)),
            ],
        ),
        migrations.CreateModel(
            name='Answers',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('answer_value', models.PositiveIntegerField()),
            ],
        ),
        migrations.CreateModel(
            name='Courses',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('course_code', models.CharField(max_length=5)),
                ('course_name', models.CharField(max_length=200)),
            ],
        ),
        migrations.CreateModel(
            name='Deadline',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('deadline_name', models.CharField(max_length=100)),
                ('deadline_datetime', models.DateTimeField(verbose_name='deadline_datetime')),
                ('deadline_course', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='Feeder11.Courses')),
            ],
        ),
        migrations.CreateModel(
            name='FeedbackForm',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('feedback_name', models.CharField(max_length=100)),
                ('feedback_deadline', models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='Feeder11.Deadline')),
            ],
        ),
        migrations.CreateModel(
            name='Instructor',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('instructor_email', models.CharField(max_length=100)),
                ('instructor_password', models.CharField(max_length=20)),
            ],
        ),
        migrations.CreateModel(
            name='Question',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('question_name', models.CharField(max_length=500)),
            ],
        ),
        migrations.CreateModel(
            name='Student',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('roll_number', models.CharField(max_length=9)),
                ('student_name', models.CharField(max_length=50)),
            ],
        ),
        migrations.AddField(
            model_name='feedbackform',
            name='feedback_questions',
            field=models.ManyToManyField(to='Feeder11.Question'),
        ),
        migrations.AddField(
            model_name='courses',
            name='course_instructors',
            field=models.ManyToManyField(blank=True, null=True, to='Feeder11.Instructor'),
        ),
        migrations.AddField(
            model_name='courses',
            name='enrolled_students',
            field=models.ManyToManyField(blank=True, null=True, to='Feeder11.Student'),
        ),
        migrations.AddField(
            model_name='answers',
            name='answer_question',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='Feeder11.Question'),
        ),
        migrations.AddField(
            model_name='answers',
            name='answer_student',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to='Feeder11.Student'),
        ),
    ]
