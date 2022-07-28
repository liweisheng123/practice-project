山东大学网络空间安全学院（研究院）2022年网络空间安全创新创业实践课程相关实践项目

全部内容由 李苇昇——202000460106 完成，账户名称：liweisheng123

完成项目：

Real world cryptanalyses（均位于同名文件夹中）

Project1: Find a key with hash value “sdu_cst_20220610” under a message composed of your name followed by your student ID. For example, “San Zhan 202000460001”.

Project2: Find a 64-byte message under some  fulfilling that their hash value is symmetrical

未完成项目：

SM3

Project: implement the naïve birthday attack of reduced SM3

Project: implement the Rho method of reduced SM3

Project: implement length extension attack for SM3, SHA256, etc.

Project: do your best to optimize SM3 implementation (software)

Project: Impl Merkle Tree following RFC6962

Project: Try to Implement this scheme


SM2

*Project: report on the application of this deduce technique in Ethereum with ECDSA

*Project: impl sm2 with RFC6979

*Project: verify the above pitfalls with proof-of-concept code

*Project: Implement the above ECMH scheme

*Project: Implement a PGP scheme with SM2

*Project: implement sm2 2P sign with real network communication

*Project: PoC impl of the scheme, or do implement analysis by Google

*Project: implement sm2 2P decrypt with real network communication

Bitcoin

Project: forge a signature to pretend that you are Satoshi

Bitcoin-public

*Project: send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself

*Project: forge a signature to pretend that you are Satoshi

Eth-public

Project: research report on MP

Real world zk

Project Idea 1. Write a circuit to prove that your CET6 grade is larger than 425. a. Your grade info is like (cn_id, grade, year, sig_by_moe). These grades are published as commitments onchain by MoE. b. When you got an interview from an employer, you can prove to them that you have passed the exam without letting them know the exact grade. 2. The commitment scheme used by MoE is SHA256-based. a. commit = SHA256(cn_id, grade, year, sig_by_moe, r)

参考资料及引用：

https://github.com/cmuratori/meow_hash

https://peter.website/meow-hash-cryptanalysis
