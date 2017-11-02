# BSGS
解$ A ^ x \equiv B (mod C) $（C是质数）
设$ m = \lceil \sqrt{C} \rceil $
$ x = i * m - j $
原式变为$ A ^ {i * m - j} \equiv B (mod C)$
再变为$ A ^ j * B \equiv A ^ {m * i} (mod C) $
枚举$ j \in [0, m] $，将$ A ^ j * B $存入哈希表
枚举$ i \in [1, m] $，从哈希表中寻找第一个满足$ A ^ j * B \equiv A ^ {m * i} (mod C) $
此时$ x = i * m - j $即为所求

