data = [60, 50, 20, 35, 40, 91, 65, 110, 70, 10]


def quicksort(data, left, right):  # 輸入資料，和從兩邊開始的位置
    if left >= right:            # 如果左邊大於右邊，就跳出function
        return

    i = left                      # 左邊的代理人
    j = right                     # 右邊的代理人
    key = data[left]                 # 基準點

    while i != j:
        while data[j] > key and i < j:   # 從右邊開始找，找比基準點小的值
            j -= 1
        while data[i] <= key and i < j:  # 從左邊開始找，找比基準點大的值
            i += 1
        if i < j:                        # 當左右代理人沒有相遇時，互換值
            data[i], data[j] = data[j], data[i]
        # print(str(i)+' '+str(j))

    # 將基準點歸換至代理人相遇點
    data[left], data[j] = data[j], data[left]
    print(key)
    print(data)
    quicksort(data, left, j-1)   # 繼續處理較小部分的子循環
    quicksort(data, j+1, right)  # 繼續處理較大部分的子循環


quicksort(data, 0, len(data)-1)
print(data)
