#!/usr/bin/env python
# -*- coding:utf-8 -*-

from sys import argv
import subprocess
import time
import tkinter as tk

print("*******************************************")
print("*                                         *")
print("*         BENCHMARK WEB LANGUAGES         *")
print("*                                         *")
print("*******************************************\n")

#subprocess.call(["TIMEFORMAT='%R'"]) #Formato solo en segundos y solo el real time

subprocess.call(['echo','>',"python-bubble.dat"])
subprocess.call(['echo','>',"perl-bubble.dat"])
subprocess.call(['echo','>',"php-bubble.dat"])
subprocess.call(['echo','>',"read.dat"])
subprocess.call(['echo','>',"write.dat"])


f = open('python-bubble.dat','w')
g = open('perl-bubble.dat','w')
h = open('php-bubble.dat','w')

print("*****************************************************\n")
print("Your system specs are: \n")
subprocess.call(['lscpu'])
print("*****************************************************\n")

print("We are going to execute the following scripts and measure the execution time.\n")

print("First of all, let's execute the BubbleSort algorithm in each language.\n")

medium_python = []
medium_php = []
medium_perl = []
media_python = 0
media_perl = 0
media_php = 0
index = 0
orden = 1 #This value is going to be necessary to determinate the order of scripts execution

for i in range(1000, 10000,1000):
    medium_python.append(0)
    medium_perl.append(0)
    medium_php.append(0)

for i in range(0,10,1):
    orden = orden + 1
    if(orden > 3):
        orden = 1
    index = 0
    for i in range(1000, 10000, 1000):
            #f.write(str(i)+" ")
            #g.write(str(i)+" ")
            #h.write(str(i)+" ")

            if(orden == 1):
                print("PYTHON\n")
                start = time.time()
                subprocess.call(['python','bubblesort.py',str(i)])
                end = time.time()
                medium_python[index] = medium_python[index] + (end - start)
                #f.write(str(data)+"\n")

                print("PHP\n")
                start = time.time()
                subprocess.call(['php','bubblesort.php',str(i)])
                end = time.time()
                medium_php[index] = medium_php[index] + (end - start)
                #h.write(str(data)+"\n")

                print("PERL\n")
                start = time.time()
                subprocess.call(['perl','bubblesort.pl',str(i)])
                end = time.time()
                medium_perl[index] = medium_perl[index] + (end - start)
                #g.write(str(data)+"\n")
            if(orden == 2):
                print("PHP\n")
                start = time.time()
                subprocess.call(['php','bubblesort.php',str(i)])
                end = time.time()
                medium_php[index] = medium_php[index] + (end - start)
                #h.write(str(data)+" ")

                print("PERL\n")
                start = time.time()
                subprocess.call(['perl','bubblesort.pl',str(i)])
                end = time.time()
                medium_perl[index] = medium_perl[index] + (end - start)
                #g.write(str(data)+"\n")

                print("PYTHON\n")
                start = time.time()
                subprocess.call(['python','bubblesort.py',str(i)])
                end = time.time()
                medium_python[index] = medium_python[index] + (end - start)
                #f.write(str(data)+" ")
            if(orden == 3):
                print("PERL\n")
                start = time.time()
                subprocess.call(['perl','bubblesort.pl',str(i)])
                end = time.time()
                medium_perl[index] = medium_perl[index] + (end - start)
                #g.write(str(data)+"\n")

                print("PHP\n")
                start = time.time()
                subprocess.call(['php','bubblesort.php',str(i)])
                end = time.time()
                medium_php[index] = medium_php[index] + (end - start)
                #h.write(str(data)+" ")

                print("PYTHON\n")
                start = time.time()
                subprocess.call(['python','bubblesort.py',str(i)])
                end = time.time()
                medium_python[index] = medium_python[index] + (end - start)
                #f.write(str(data)+" ")

            index = index + 1



index = 0
for i in range(1000, 10000,1000):
    f.write(str(i)+" ")
    g.write(str(i)+" ")
    h.write(str(i)+" ")

    f.write(str(medium_python[index]/10) + "\n")
    g.write(str(medium_perl[index]/10) + "\n")
    h.write(str(medium_php[index]/10) + "\n")

    index = index + 1

f.close()
g.close()
h.close()

#####################################
print("Now let's creat the file for testing reading a file, the size of the file is 50MB\n")
subprocess.call(['dd','if=/dev/zero','of=testfile_50MB','bs=50485760','count=1'])


media_python2 = 0
media_php2 = 0
media_perl2 = 0
print("Now test reading a file. We are going to do two test in one. We are going to read from RAM and from HD\n")
#TEST LECTURA
orden = 1
for i in range(0,10,1):
    if(orden == 1):
        print("PYTHON\n")
        start = time.time()
        subprocess.call(['python','readfile.py','testfile_50MB'])
        end = time.time()
        media_python = media_python + (end - start)

        #f.write(str(data)+"\n")

        print("PHP\n")
        start = time.time()
        subprocess.call(['php','readfile.php','testfile_50MB'])
        end = time.time()
        media_php = media_php + (end - start)

        #h.write(str(data)+"\n")

        print("PERL\n")
        start = time.time()
        subprocess.call(['perl','readfile.pl','testfile_50MB'])
        end = time.time()
        media_perl = media_perl + (end - start)

        #g.write(str(data)+"\n")
    if(orden == 2):
        print("PHP\n")
        start = time.time()
        subprocess.call(['php','readfile.php','testfile_50MB'])
        end = time.time()
        media_php = media_php + (end - start)

        #h.write(str(data)+" ")

        print("PERL\n")
        start = time.time()
        subprocess.call(['perl','readfile.pl','testfile_50MB'])
        end = time.time()
        media_perl = media_perl + (end - start)

        #g.write(str(data)+"\n")

        print("PYTHON\n")
        start = time.time()
        subprocess.call(['python','readfile.py','testfile_50MB'])
        end = time.time()
        media_python = media_python + (end - start)

        #f.write(str(data)+" ")
    if(orden == 3):
        print("PERL\n")
        start = time.time()
        subprocess.call(['perl','readfile.pl','testfile_50MB'])
        end = time.time()
        media_perl = media_perl + (end - start)
        #g.write(str(data)+"\n")

        print("PHP\n")
        start = time.time()
        subprocess.call(['php','readfile.php','testfile_50MB'])
        end = time.time()
        media_php = media_php + (end - start)

        #h.write(str(data)+" ")

        print("PYTHON\n")
        start = time.time()
        subprocess.call(['python','readfile.py','testfile_50MB'])
        end = time.time()
        media_python = media_python + (end - start)


    orden = orden + 1
    if(orden > 3):
        orden = 1


f = open('read.dat','w')
f.write("0"+" "+"Python"+" "+str(media_python/10)+"\n")
f.write("1"+" "+"PHP"+" "+str(media_php/10)+"\n")
f.write("2"+" "+"Perl"+" "+str(media_perl/10)+"\n")
f.close()
#########################################
media_php = 0
media_python = 0
media_perl = 0
media_python2 = 0
media_php2 = 0
media_perl2 = 0
print("To sum up, we are going to test writing a file\n")
#TEST ESCRITURA
orden = 1
for i in range(0,10,1):
    if(orden == 1):
        print("PYTHON\n")
        start = time.time()
        subprocess.call(['python','writefile.py','write-py.txt'])
        end = time.time()
        media_python = media_python + (end - start)

        #f.write(str(data)+"\n")

        print("PHP\n")
        start = time.time()
        subprocess.call(['php','writefile.php','write-php.txt'])
        end = time.time()
        media_php = media_php + (end - start)

        #h.write(str(data)+"\n")

        print("PERL\n")
        start = time.time()
        subprocess.call(['perl','writefile.pl','write-pl.txt'])
        end = time.time()
        media_perl = media_perl + (end - start)

        #g.write(str(data)+"\n")
    if(orden == 2):
        print("PHP\n")
        start = time.time()
        subprocess.call(['php','writefile.php','write-php.txt'])
        end = time.time()
        media_php = media_php + (end - start)
        start = time.time()

        #h.write(str(data)+" ")

        print("PERL\n")
        start = time.time()
        subprocess.call(['perl','writefile.pl','write-pl.txt'])
        end = time.time()
        media_perl = media_perl + (end - start)
        start = time.time()


        print("PYTHON\n")
        start = time.time()
        subprocess.call(['python','writefile.py','write-py.txt'])
        end = time.time()
        media_python = media_python + (end - start)
        start = time.time()

    if(orden == 3):
        print("PERL\n")
        start = time.time()
        subprocess.call(['perl','writefile.pl','write-pl.txt'])
        end = time.time()
        media_perl = media_perl + (end - start)
        start = time.time()


        print("PHP\n")
        start = time.time()
        subprocess.call(['php','writefile.php','write-php.txt'])
        end = time.time()
        media_php = media_php + (end - start)

        #h.write(str(data)+" ")

        print("PYTHON\n")
        start = time.time()
        subprocess.call(['python','writefile.py','write-py.txt'])
        end = time.time()
        media_python = media_python + (end - start)


    orden = orden + 1
    if(orden > 3):
            orden = 1

f = open('write.dat','w')
f.write("0"+" "+"Python"+" "+str(media_python/10)+"\n")
f.write("1"+" "+"PHP"+" "+str(media_php/10)+"\n")
f.write("2"+" "+"Perl"+" "+str(media_perl/10)+"\n")
f.close()



######################################

print("Plotting the graphs\n")
subprocess.call(['gnuplot','gnuplot.gp'])

######################################

print("Deleting all the trash\n")

subprocess.call(['rm','write-py.txt','write-php.txt','write-pl.txt'
,'testfile_50MB'])

################################################

#This it's going to show the results in a pop-up window
print("Showing results\n")

root = tk.Tk()
root.title("Benchmark Web languages")
photo = tk.PhotoImage(file= r"writefile.gif")
photo2 = tk.PhotoImage(file = r"readfile.gif")
photo3 = tk.PhotoImage(file = r"bubblesortbenchmark.gif")
cv = tk.Canvas(root,width=2000, height=2000)
cv.pack(side='top', fill='both', expand='yes')
cv.create_text(950,100,font=("Purisa", 50),text = "BENCHMARK WEB LANGUAGES")
cv.create_image(5, 200, image=photo, anchor='nw')
cv.create_image(645, 200, image=photo2, anchor='nw')
cv.create_image(1280, 200, image=photo3, anchor='nw')
root.mainloop()
