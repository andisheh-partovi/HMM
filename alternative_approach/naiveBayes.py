__author__ = 'dan'
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats



for a in range(1,10):
	counter = {'A': 0, 'H': 0}

	data = pd.read_csv('data/house' + str(a) + '.txt',header=None, delimiter="\t")

	#f = open('data'+ str(a) +'.txt', 'a')
	s1 = data.groupby([1])[0].std()
	s1.name = 'std'
	s2 = data.groupby([1])[0].mean()
	s2.name = 'mean'
	df = pd.concat([s1, s2], axis=1)

	dat = (0,0)
	for i in range(1,48):
		total = df.loc[i,'std'] + df.loc[i,'mean']
		if dat[1] > total or dat[1] == 0:
			dat = (i , total, df.loc[i,'mean'],  df.loc[i,'std'])

	"""print away distribution"""
	#print dat

	data2 = data[data[0] > dat[2]]
	sortFat = sorted(data2[0])
	sortedd =  sorted(data[0])


	data2 = data[data[0] > (dat[2] + dat[3]*3)]

	s1 = data2.groupby([1])[0].std()
	s1.name = 'std'
	s2 = data2.groupby([1])[0].mean()
	s2.name = 'mean'
	df = pd.concat([s1, s2], axis=1)

	mean = 0
	std = 0
	"""Get dinner average"""
	for i in range(34,44):
		"""plot ranges before averaging"""
		#plt.plot(sortedd, stats.norm.pdf(sortedd,df.loc[i,'mean'],df.loc[i,'std']))
		mean = df.loc[i,'mean'] + mean
		std = df.loc[i,'std'] + mean
	mean = mean /10
	std = std /10
	plt.plot(sortedd, stats.norm.pdf(sortedd,mean,std))

	""" For breakfast calculation"""
	#meanBrec = 0
	#stdBrec = 0
	#for i in range(13,17):
		#"""plot ranges before averaging"""
		#plt.plot(sortFat, stats.norm.pdf(sortFat,df.loc[i,'mean'],df.loc[i,'std']))
	#	meanBrec = df.loc[i,'mean'] + meanBrec
	#	stdBrec = df.loc[i,'std'] + stdBrec
	#meanBrec = mean /4
	#stdBrec = std /4

	location = ""
	for x in range(1,366):
		df = data[data[2] == x]
		df = df[df[1] >= 34]
		df = df[df[1] <= 44]

		""" For breakfast calculation"""
		#print('Breakfast')
		#if home > away:
			#print str(x) + "\t" + "H" + "\t" + str(stats.norm.cdf((dfBreak[0].mean() - meanBrec) / stdBrec)) + "\t" + str(dfBreak[0].mean())
		#else:
			#print str(x) + "\t" + "A" + "\t" + str(1 - (stats.norm.cdf((dfBreak[0].mean() - dat[2]) / dat[3])))  + "\t" + str(dfBreak[0].mean())

		away = 1 - (stats.norm.cdf((df[0].mean() - dat[2]) / dat[3]))
		home = stats.norm.cdf((df[0].mean() - mean) / std)

		if home > away:
			counter['H'] += 1
			print str(x) + "\t" + "H" + "\t" + str(stats.norm.cdf((df[0].mean() - mean) / std)) + "\t" + str(df[0].mean())
		else:
			counter['A'] += 1
			print str(x) + "\t" + "A" + "\t" + str(1 - (stats.norm.cdf((df[0].mean() - dat[2]) / dat[3])))  + "\t" + str(df[0].mean())
	print counter, a

	"""Show plot"""
	sort = sorted(data[0])
	plt.plot(sort, stats.norm.pdf(sort,dat[2] ,dat[3]))
	plt.show()

