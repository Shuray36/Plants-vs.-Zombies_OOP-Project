# 待修bug

- 原本的問題 兩隻殭屍同時吃的時候，植物死掉後 第一隻吃到的殭屍才能繼續走，後面吃到的會一直吃 修改後雖然能所有殭屍一起走，但是所有殭屍的攻擊秒數會重製。

- 豌豆射手的子彈會因為距離越射越快，並不是固定的速度
- 放置會有問題

# 目標
- 能選擇關卡 ✅
- 植物的獲勝畫面✅
- 增加一種植物✅
- 增加兩種殭屍✅
- 重製功能 ✅

# 細節調整
- 殭屍召喚時間要拉長
- 之後有時間的話可以把card寫成一個class
- 放完植物後應該要有冷卻時間
- 太陽花的太陽生成位置可以改好一點
- 把殭屍寫成class重構

# 快捷鍵
- r鍵：reset
- 方向鍵 上：回到開始畫面
- 方向鍵 下：所有車子直接跑
- m鍵：+錢錢
- 1-5鍵：分別是1-5的道路產生殭屍
- o鍵：殭屍直接勝利
- p鍵：植物直接勝利
- j鍵：召喚一般殭屍
- k鍵：召喚三角錐殭屍
- L鍵：召喚鐵桶殭屍

# 細節調整說明
- 把子彈寫成一個class了 叫pb
- 重新寫了一下植物攻擊的邏輯，現在不會因為殭屍的距離而改變攻擊的速度了