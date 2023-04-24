from matplotlib import pyplot as plt

stateX = []
stateY = []
bestStateX = []
bestStateY = []

with open("StateHistory.txt", 'r') as textFile:
    length = int(textFile.readline())
    maxIter = int(textFile.readline())
    print("length is ", length)
    fig, ((ax1, ax2)) = plt.subplots(1, 2)
    
    done = False
    
    for j in range(maxIter):
        stateX = []
        stateY = []
        bestStateX = []
        bestStateY = []
        
        for i in range(length+1):
            coordinate = textFile.readline().rstrip().split(",")
            if coordinate == ['']:
                done = True
                break
            stateX.append(float(coordinate[0]))
            stateY.append(float(coordinate[1]))
            
        for i in range(length+1):
            coordinate = textFile.readline().rstrip().split(",")
            
            if coordinate == ['']:
                done = True
                break
            
            bestStateX.append(float(coordinate[0]))
            bestStateY.append(float(coordinate[1]))
        
        #print(len(stateX))
        j =j + 1
        ax1.cla()
        ax1.plot(stateX,stateY)
        ax2.cla()
        ax2.plot(bestStateX,bestStateY)
        ax1.set_title('Best at current iteration',fontsize=11)
        ax2.set_title('Best overall',fontsize=11)
        fig.suptitle(['SA Traveling Salesman Iteration # ',j])
        
        plt.pause(0.005)


