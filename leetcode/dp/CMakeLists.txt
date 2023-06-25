project(dp)

# DP 介绍 ----------------------------------------------------------------------
add_executable(0509 0509_fibonacci_number.cc)
add_executable(0070 0070_climbing_stairs.cc) # 存在完全背包转化
add_executable(0746 0746_min_cost_climbing_stairs.cc)

# 一/二维 DP -------------------------------------------------------------------
add_executable(0062 0062_unique_paths.cc)
add_executable(0063 0063_unique_paths_II.cc)
add_executable(0343 0343_integer_break.cc)
add_executable(0096 0096_unique_binary_search_trees.cc)
# add_executable(0095 0095_unique_binary_search_trees_II.cc)

# 0-1 背包 ---------------------------------------------------------------------
add_executable(0416 0416_partition_equal_subset_sum.cc)
add_executable(1049 1049_last_stone_weight_ii.cc)
add_executable(0494 0494_target_sum.cc) # another method backtrace
add_executable(0474 0474_ones_and_zeroes.cc)


add_executable(0956 0956_tallest_billboard.cc) # (难题 高度差)
#2035. Partition Array Into Two Arrays to Minimize Sum Difference

# 完全背包 ---------------------------------------------------------------------
add_executable(0518 0518_coin_change_2.cc)
add_executable(0377 0377_combination_sum_iv.cc)
add_executable(0322 0322_coin_change.cc)
add_executable(0279 0279_perfect_squares.cc)
add_executable(0139 0139_word_break.cc) # 使用排列顺序, 为什么不用组合顺序?

add_executable(0003 0003_longest_substring_without_repeating_characters.cc)

#add_executable(0647 0647_palindromic_substrings.cpp)
#add_executable(0005 0005_longest_palindromic_substring.cpp)

add_executable(1799 1799_maximize_score_after_n_operations.cc) # 难题(dp 压缩 mask) *

add_executable(2140 2140_solving_questions_with_brainpower.cc) # 简单题 (一维 遍历方向)
add_executable(2466 2466_count_ways_to_build_good_strings.cc) # 简单题 (一维)
#120. Triangle
#354. Russian Doll Envelopes
#1349. Maximum Students Taking Exam
add_executable(1143 1143_longest_common_subsequence.cc) # 简单题 (LCS)
add_executable(1035 1035_uncrossed_lines.cc) # 简单题 (LCS)
add_executable(1027 1027_longest_arithmetic_subsequence.cc) #(LCS 额外状态)

add_executable(0300 0300_longest_increasing_subsequence.cc) # 简单题 (动态规划/贪心二分 LIS)
#334. Increasing Triplet Subsequence
#354. Russian Doll Envelopes
#646. Maximum Length of Pair Chain
add_executable(1964 1964_find_the_longest_valid_obstacle_course_at_each_position.cc) # 中等题 (贪心二分 LIS)
#1439. Find the Kth Smllest Sum of a Matrix With Sorted Rows
#2560. House Robber IV
#2659. Make Array Empty

add_executable(0837 0837_new_21_game.cc)   # 难题(滑动窗口/概率统计) *

add_executable(0877 0877_stone_game.cc)     # 简单题(零和博弈/记忆/二维)
add_executable(1140 1140_stone_game_ii.cc)  # 难题(零和博弈/记忆)
add_executable(1406 1406_stone_game_iii.cc) # 简单题(零和博弈/记忆)
#1563. Stone Game V
#1686. Stone Game VI
#1690. Stone Game VII

add_executable(1547 1547_minimum_cost_to_cut_a_stick.cc) # 中等题(二维)


# 两个数组交换元素, 组成递增数组问题
add_executable(0801 0801_minimum_swaps_to_make_sequences_increasing.cc) # 中等题(二维)
add_executable(1187 1187_make_array_strictly_increasing.cc) # 难题*

add_executable(2328 2328_number_of_increasing_paths_in_a_grid.cc) # 中等题 (DFS/记忆)


add_executable(1575 1575_count_all_possible_routes.cc) # 难题

