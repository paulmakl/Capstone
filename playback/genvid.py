f = open('video.txt','w')
f.write("$size\n64,64,64,8000\n")
i = 0.05
j = 0
while( i < 50.0):
	f.write("$" + str( j ) + "\n")
	#f.write("$" + str( int(i / 0.05) - 1 ) + "\n")
	for x in range(0, 8000):
		f.write( str(i + 0.5) + "," + str(i + 0.05) + "," + str(i + 0.05) + "\n" )
	i += 0.5
	j += 1
