# Minesweeper

## 功能列表
### - **基本功能**
1. 開頭功能選單
2. 15 顆地雷隨機分佈在 10×10 大小的遊戲區域內，並於區域內的每個位置(地雷所在的位置除外)計算出其周圍有多少顆地雷。
3. 可指定遊戲區域內的任意位置(輸入一組 X,Y 座標)進行開啟或標記地雷的動作(開啟過的位置不可再選擇，標記過的位置可取消標記)。
4. 正確判斷遊戲是否結束；若踩到地雷即失敗並且印出所有地雷位置；若區域內所有非地雷位置皆被開啟且地雷標記都正確時，即為勝利。
5. 遊戲中會顯示剩餘地雷個數，同時計算步數。
6. 避免違反規則的動作發生。




### - **進階功能**
1. 動畫及美編設計


   (1) 利用延遲製造動畫效果


   (2) 更改背景及文字顏色增加視覺化呈現


   (3) 以彈出視窗顯示遊戲結果

   
   
2. 提供使用者自訂遊戲區域大小及地雷個數
   > 遊戲區域大小上限為30*30，地雷個數上限為250


   (1) 若所輸入數字超過上限或為負數，則會要求使用者重新輸入

   
   (2) 若輸入地雷數超過遊戲區域所能容納大小，則會要求使用者重新輸入
   
3. 顯示遊戲遊玩時間
4. 若開啟一個其周圍都沒有地雷的位置，則會同時開啟一整片區域，直到遇到周圍存在地雷的位置為止
5. 遊戲操作過程中可輸入指定格式結束遊戲
6. 踩到地雷而遊戲結束後會顯示出標記的正確與否，並於正確的標記上加上不同色彩



## flow-chart
https://miro.com/app/board/uXjVOseqBXo=/?share_link_id=154219146030


## demo
https://drive.google.com/file/d/1OQ2ZEo-scmc2jp2X6aySwfWFgiNEZ7QI/view

<video width="640" height="360" controls>
  <source src="https://drive.google.com/uc?export=download&id=1OQ2ZEo-scmc2jp2X6aySwfWFgiNEZ7QI" type="video/mp4">
  Your browser does not support the video tag.
</video>

