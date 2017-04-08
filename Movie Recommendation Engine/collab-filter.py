import csv
file1=open('movie-ratings.csv','r')
read1=csv.reader(file1)
data=[]
for line in read1:
	data.append(line)
movie=data[0];
data.pop(0)
movie.pop(0);
ratings=[]
critic_name=[];
for list in data:
	critic_name.append(list[0])
	del list[0];
	dictn=dict((movie[i],float(list[i])) for i in range(len(movie)));
	ratings.append(dictn)

file2=open('user_preference.csv','r')
read2=csv.reader(file2)
user_data=[]
for line in read2:
	user_data.append(line)
user_dic=dict(zip(user_data[0],user_data[1]))
for moviename in user_dic:
	user_dic[moviename]=float(user_dic[moviename])

from math import sqrt
corr_coeff=[];
for critic in ratings:
	xy=[]
	x=[]
	y=[]
	x_square=[]
	y_square=[]
	for i in user_dic.keys():
		if critic[i]!=-1 and user_dic[i]!=-1:
			xy.append(critic[i]*user_dic[i])
			x.append(critic[i])
			y.append(user_dic[i])
			x_square.append(critic[i]**2)
			y_square.append(user_dic[i]**2)
	n=len(xy)
	if n*sum(x_square)-sum(x)*sum(x)!=0 and n*sum(y_square)-sum(y)*sum(y)!=0:
		corr_coeff.append((n*sum(xy)-sum(x)*sum(y))/(sqrt(n*sum(x_square)-sum(x)*sum(x))*sqrt(n*sum(y_square)-sum(y)*sum(y))))
	else:
		corr_coeff.append(0)
pearson_order=sorted(zip(critic_name,corr_coeff), key=lambda x:x[1],reverse=True)
#[print(pearson_order[i][0])for i in range(len(pearson_order))] 

movie_rating={}
for moviename in movie:
	weight_rating=[]
	sum_corr_coeff=[]
	for i in range(len(corr_coeff)):
		if ratings[i][moviename]!=-1:
			weight_rating.append(corr_coeff[i]*ratings[i][moviename])
			sum_corr_coeff.append(abs(corr_coeff[i]))
	movie_rating[moviename]=sum(weight_rating)/sum(sum_corr_coeff);
rating_order=sorted(movie_rating,key=movie_rating.__getitem__,reverse=True)

i=1
for movie in rating_order:
	if user_dic[movie]==-1 and i<4:
		print(movie)
		i=i+1