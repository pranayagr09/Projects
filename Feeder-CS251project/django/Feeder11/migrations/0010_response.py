# -*- coding: utf-8 -*-
# Generated by Django 1.10.2 on 2016-11-05 16:13
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Feeder11', '0009_question_question_id'),
    ]

    operations = [
        migrations.CreateModel(
            name='response',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('response1', models.PositiveIntegerField()),
                ('response2', models.PositiveIntegerField()),
                ('response3', models.PositiveIntegerField()),
                ('response4', models.PositiveIntegerField()),
                ('response5', models.PositiveIntegerField()),
            ],
        ),
    ]
