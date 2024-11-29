from re import L
import numpy as np
from tensorflow.keras.models import load_model
import random
# Generate a single noise vector

def hello():
    return "Hello from FinalDungeonGen.py!"
def DungeonGen():
  # Load the generator model
  generator = load_model('generator_model.keras')

  random_dim = 100  # Ensure this matches the random_dim used in training
  single_noise = np.random.normal(0, 1, (1, random_dim)).astype(np.float32)

  # Generate a single output from the generator
  single_output = generator.predict(single_noise, verbose=0)

  # Threshold the output to get an array of 1s and 0s
  binary_output = (single_output > 0.5).astype(int)  # Convert values to 1s and 0s

  # Reshape and print the binary output as a 20x20 grid
  binary_layout = binary_output.reshape(20, 20)  # Assuming a 20x20 layout
  # print("Generated Dungeon Layout (Binary Array):")
  # print(binary_layout)


  received_M = random.randint(3, 18)
  received_N = random.randint(3, 18)

  M = 19 - received_M
  N = 19 - received_N
  binary_layout[M,N] = 1

  M = random.randint(0, M)
  N = random.randint(0, N)
  binary_layout = np.array(binary_layout)
  subset = binary_layout[M:M+received_M, N:N+received_N]

  # end of subset gen


  def depth_first_search(i, j, graph):
      if i < 0 or i >= len(graph) or j < 0 or j >= len(graph[0]):
          return 0, False
      if graph[i][j] == -5:
          return -5, False
      if graph[i][j] != 1:
          return 0, False
      else:
          graph[i][j] = -5


      downLength, downResult =  depth_first_search(i + 1, j, graph)
      valueToReturn = 0
      boolToReturn = False
      if i != 0:
        leftLength, leftResult = depth_first_search(i , j-1, graph)
        rightLength, rightResult = depth_first_search(i, j+1, graph)
        if downLength > rightLength and downLength > leftLength :
          valueToReturn, boolToReturn =  downLength, downResult
        elif rightLength > downLength and rightLength > leftLength :
          valueToReturn, boolToReturn =  rightLength, rightResult
        elif leftLength > downLength and leftLength > rightLength :
          valueToReturn, boolToReturn =  leftLength, leftResult
        elif downLength == rightLength and downLength > leftLength :
          valueToReturn, boolToReturn =  downLength, downResult
          rightLength = -rightLength
          if(j+1 < len(graph[i])):
            graph[i][j+1] = -graph[i][j+1]
        elif downLength == leftLength and downLength > rightLength :
          valueToReturn, boolToReturn =  downLength, downResult
          leftLength = -leftLength
          if(j-1 > 0):
            graph[i][j-1] = -graph[i][j-1]
        elif rightLength == leftLength and rightLength > downLength :
          valueToReturn, boolToReturn =  leftLength, leftResult
          rightLength = -rightLength
          if(j+1 < len(graph[i])):
            graph[i][j+1] = -graph[i][j+1]
      else:
        valueToReturn, boolToReturn = downLength, downResult
      if valueToReturn == 0:
        valueToReturn = 21
      graph[i][j] = valueToReturn


      return valueToReturn+1, boolToReturn

  new_subset = subset.copy()
  for i in range(len(new_subset[0])):
    if(new_subset[0][i] == 1):
      new_subset[0][i], final = depth_first_search(0, i, new_subset)

  result = 0
  for i in new_subset[0]:
    if i > result:
      result = i

  result_index = 0

  for i in range(len(new_subset)):
    for j in range(len(new_subset[i])):
      if new_subset[i][j] >= 21:
        result_index += 1
        for k in range(len(new_subset[i])):
          if new_subset[i][k] <= 20:
            new_subset[i][k] = 0
  if result_index == 0:
    result_index = random.randint(0, len(new_subset[0]) - 1)
    new_subset[0][result_index] = 1

  largest = 0
  largest_index = -1
  correct_route = []
  for i in range(len(new_subset[0])):
    if largest < new_subset[0][i]:
      largest = new_subset[0][i]
      largest_index = i

    elif largest == new_subset[0][i] and largest_index != i:
      new_subset[0][i] = -new_subset[0][i]
  correct_route.append([0, largest_index])
  final_value = -1
  latest_second_row = correct_route[len(correct_route)-1][0]
  latest_second_col = correct_route[len(correct_route)-1][1]

  latest_value = new_subset[latest_second_row][latest_second_col]
  second_index =new_subset[correct_route[len(correct_route)-1][0]+1][correct_route[len(correct_route)-1][1]]
  if ( second_index == latest_value - 2):
    correct_route.append([correct_route[len(correct_route)-1][0]+1,correct_route[len(correct_route)-1][1]])



  shit = 1

  latest_row = correct_route[len(correct_route)-1][0]
  latest_col = correct_route[len(correct_route)-1][1]
  if(second_index != 21):
    while final_value != 21 and new_subset[latest_row][latest_col] != 22:
      shit+=1
      if(shit %10000 == 0):
        print("shit : " + str(shit))
        print("row " + str(latest_row) + " col " + str(latest_col))
      latest_row = correct_route[len(correct_route)-1][0]
      latest_col = correct_route[len(correct_route)-1][1]
      if(latest_row + 1 < len(new_subset) and new_subset[latest_row +1][latest_col] == new_subset[latest_row][latest_col] - 1):
        final_value = new_subset[latest_row+1][latest_col]
        correct_route.append([latest_row+1, latest_col])
      elif(latest_col + 1 <len(new_subset[latest_row]) and new_subset[latest_row][latest_col + 1] == new_subset[latest_row][latest_col] - 1):
        final_value = new_subset[latest_row][latest_col+1]
        correct_route.append([latest_row, latest_col+1])
      elif(latest_col - 1 >= 0 and new_subset[latest_row][latest_col - 1] == new_subset[latest_row][latest_col] - 1):
        final_value = new_subset[latest_row][latest_col-1]
        correct_route.append([latest_row, latest_col-1])

  for i in range(len(correct_route)):
    new_subset[correct_route[i][0]][correct_route[i][1]] = 99
  for i in range(0, correct_route[len(correct_route)-1][0] + 1):
    for j in range(0, len(new_subset[i])):
      if new_subset[i][j] != 99:
        new_subset[i][j] = 0
  last_row = correct_route[len(correct_route)-1][0]
  for j in range(len(new_subset[last_row])):
    if(new_subset[last_row][j] == 99 and new_subset[last_row-1][j] != 99):
      new_subset[i][j] = 0




  for i in range(correct_route[len(correct_route)-1][0] + 1, len(new_subset)):
    for j in range(0, len(new_subset[i])):
        new_subset[i][j] = 0



  def line_fix(line, grid, previous):
    for i in range(len(grid[line])):
      if grid[line][i] == 1:
        current = i
    if(previous > current):
      lesser = current
      greater = previous
    elif previous < current:
      lesser = previous
      greater = current
    if current != previous:
      for i in range(lesser, greater+1):
        if grid[line-1][i] == 0:
          grid[line-1][i] = 1
    if(line+1 < len(grid)):
      line_fix(line+1, grid, current)


  for i in range(correct_route[len(correct_route)-1][0]+1, len(new_subset)):
    new_subset[i][random.randint(0,len(new_subset[i])-1)] = 1
  if(correct_route[len(correct_route)-1][0]+1 < len(new_subset)):
    line_fix(correct_route[len(correct_route)-1][0]+1, new_subset, correct_route[len(correct_route)-1][1])

  for i in range(len(new_subset)):
    for j in range(len(new_subset[i])):
      if new_subset[i][j] == 99:
        new_subset[i][j] = 1


  array_string = np.array2string(new_subset, separator=' ')
  print(array_string)
  return array_string
