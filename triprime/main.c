#include <stdio.h>
#include <unistd.h>
 
#define MAXCIUR 10000000
 
#define MAXN 390000000
 
int ciur[MAXCIUR];
int prime[MAXCIUR], primeCnt;
 
int v[2000] = {
0, 40477, 41452, 41723, 41620, 41692, 41884, 41827, 41693, 41736, 42022, 41827, 41624, 41861, 41776, 41912, 42034, 41708, 41678, 41827, 41825, 41738, 41702, 41922, 41917, 41991, 41696, 41831, 41676, 41575, 41826, 41814, 41629, 41751, 41850, 41962, 41901, 41699, 41657, 41671, 41856, 41622, 41804, 41731, 42039, 41457, 41797, 41643, 41673, 41528, 41590, 41694, 41773, 41798, 41787, 41770, 41739, 41698, 41845, 41726, 41742, 41682, 41774, 41549, 41822, 41674, 41575, 41531, 41598, 41664, 41601, 41371, 41911, 41585, 41671, 41549, 41724, 41509, 41875, 41405, 41635, 41684, 41536, 41815, 41745, 41798, 41430, 41751, 41705, 41620, 41647, 41522, 41695, 41487, 41602, 41627, 41631, 41716, 41554, 41557, 41794, 41458, 41669, 41512, 41587, 41462, 41464, 41583, 41579, 41727, 41589, 41352, 41411, 41710, 41645, 41586, 41474, 41617, 41473, 41507, 41514, 41636, 41713, 41497, 41542, 41421, 41526, 41461, 41493, 41551, 41618, 41426, 41547, 41726, 41443, 41754, 41675, 41391, 41526, 41528, 41604, 41519, 41689, 41412, 41340, 41647, 41417, 41721, 41309, 41571, 41909, 41592, 41618, 41530, 41688, 41376, 41178, 41496, 41403, 41432, 41569, 41497, 41680, 41408, 41603, 41321, 41480, 41598, 41321, 41434, 41371, 41321, 41382, 41373, 41231, 41356, 41290, 41514, 41544, 41576, 41246, 41604, 41733, 41198, 41426, 41498, 41394, 41431, 41557, 41515, 41426, 41424, 41504, 41515, 41558, 41618, 41624, 41596, 41430, 41604, 41210, 41409, 41694, 41515, 41512, 41326, 41338, 41265, 41333, 41406, 41511, 41519, 41582, 41456, 41224, 41263, 41312, 41398, 41405, 41331, 41396, 41431, 41430, 41608, 41611, 41449, 41453, 41612, 41456, 41394, 41353, 41433, 41377, 41250, 41426, 41273, 41606, 41352, 41566, 41256, 41295, 41422, 41304, 41196, 41177, 41602, 41442, 41313, 41452, 41423, 41635, 41287, 41371, 41590, 41307, 41357, 41349, 41347, 41470, 41364, 41287, 41287, 41451, 41318, 41330, 41228, 41393, 41262, 41377, 41439, 41174, 41279, 41407, 41517, 41119, 41366, 41361, 41375, 41279, 41539, 41207, 41590, 41408, 41135, 41618, 41348, 41539, 41158, 41351, 41271, 41302, 41330, 41364, 41266, 41436, 41540, 41337, 41089, 41490, 41129, 41141, 41188, 41361, 41253, 41338, 41471, 41239, 41207, 41199, 41260, 41502, 41408, 41451, 41265, 41422, 41406, 41290, 41482, 41325, 41247, 41352, 41379, 41262, 41234, 41187, 41266, 41108, 41337, 41475, 41279, 41330, 41460, 41525, 41316, 41276, 41311, 41378, 41562, 41396, 41139, 41399, 41264, 41454, 41276, 41434, 41224, 41227, 41514, 41239, 41361, 41254, 41534, 41324, 41320, 41242, 41249, 41467, 41262, 41356, 41290, 41227, 41309, 41446, 41076, 41219, 41348, 41161, 41523, 41253, 41463, 41098, 41137, 41071, 41576, 41198, 41327, 41188, 41325, 41358, 41516, 41305, 41239, 41102, 41017, 41236, 41386, 41348, 41162, 40936, 41102, 41279, 41212, 41193, 41270, 41285, 41179, 41232, 41076, 41209, 41341, 41134, 41391, 41297, 41264, 41110, 41391, 41397, 41182, 41169, 41350, 41430, 41169, 41173, 41296, 41424, 41225, 41255, 41308, 41321, 40945, 41428, 41230, 41121, 41122, 41127, 41057, 41280, 41234, 41310, 41456, 41285, 41320, 41252, 41104, 41174, 41231, 41218, 41153, 41407, 41217, 41057, 41339, 41489, 41079, 41329, 41210, 40989, 41301, 41001, 41120, 40991, 41127, 41335, 41084, 41052, 41298, 41150, 41297, 41167, 41227, 41187, 41242, 41217, 41293, 41276, 41177, 41305, 41104, 41342, 41131, 41235, 41359, 41089, 41543, 41051, 41328, 41243, 41316, 41178, 41066, 41365, 41409, 41137, 41215, 41155, 41185, 41124, 41232, 41574, 41095, 41298, 41031, 41340, 41367, 41056, 40777, 41182, 41295, 41214, 40968, 41168, 41155, 41165, 41180, 41214, 41264, 41236, 41168, 41099, 41218, 41365, 41327, 41352, 41327, 41221, 41240, 41107, 41287, 40903, 41185, 41353, 41376, 41396, 41224, 41093, 41196, 41267, 41123, 41259, 41258, 41168, 41064, 41130, 41111, 41227, 41064, 41346, 41178, 41272, 41341, 41144, 41043, 41364, 41289, 41153, 41106, 41080, 41352, 41312, 41279, 41280, 41026, 41161, 41334, 41258, 41057, 41212, 40989, 40914, 41427, 41164, 41236, 41026, 40998, 41187, 41149, 41190, 41060, 41006, 41088, 41159, 41046, 41037, 40954, 41198, 41083, 41224, 41069, 41176, 41289, 41409, 40988, 40986, 41185, 40951, 41331, 40997, 41086, 41063, 41044, 41143, 41120, 41108, 41185, 41310, 40854, 41122, 41121, 41087, 41188, 41221, 41357, 41031, 41185, 41003, 40920, 41230, 41012, 41102, 41007, 41110, 41089, 41155, 41139, 41294, 41127, 41323, 41129, 41096, 41247, 41109, 41232, 41214, 41199, 41185, 41277, 41175, 41107, 40872, 41295, 41334, 41253, 41085, 41107, 40968, 41048, 41305, 41070, 41064, 40925, 41099, 41184, 41063, 41180, 41367, 41193, 41228, 41207, 41276, 41223, 40939, 41090, 41204, 41010, 41197, 41088, 41121, 41288, 41153, 41158, 40867, 40997, 41221, 40943, 40879, 41090, 41256, 40832, 41138, 41045, 41133, 41085, 41139, 40995, 41128, 41013, 40967, 41205, 40944, 40953, 40880, 41047, 41152, 41223, 41160, 41028, 41282, 40943, 41286, 40998, 41105, 41048, 41207, 41161, 40811, 41266, 41119, 40957, 41022, 41154, 41139, 40879, 41084, 41102, 41115, 40955, 41029, 41231, 41024, 41259, 41066, 41204, 41204, 40940, 41151, 41191, 41120, 41230, 41234, 41115, 41271, 41008, 40958, 40980, 41166, 40912, 41088, 41137, 41092, 41143, 41237, 41215, 41159, 41037, 40876, 41227, 41031, 41081, 41146, 40993, 41282, 41254, 40964, 41117, 41046, 41091, 41031, 40896, 40959, 40858, 41017, 41146, 40820, 41223, 41011, 40797, 41154, 40998, 40902, 40842, 40915, 41117, 41030, 41142, 41133, 41160, 41228, 40964, 41192, 41163, 41026, 40878, 40960, 41196, 41109, 41264, 41194, 41131, 40994, 40989, 41286, 41043, 41161, 41199, 41114, 41231, 40877, 41243, 41011, 41077, 40899, 40930, 41029, 41230, 40981, 41079, 40990, 41059, 41072, 41125, 41082, 41116, 41152, 40910, 41101, 41159, 40968, 40957, 41018, 40935, 40895, 40997, 40845, 41279, 41029, 40821, 41103, 41244, 40939, 41232, 41003, 41108, 41036, 41208, 41150, 41036, 40890, 40841, 40956, 40952, 41061, 41205, 41189, 41084, 41154, 40889, 40849, 41204, 41223, 41065, 40804, 41313, 40868, 40947, 41226, 41029, 41126, 41288, 41020, 41214, 41030, 41051, 41024, 41064, 40901, 41059, 41204, 40915, 41076, 41072, 41078, 40990, 41085, 41075, 40985, 41008, 41240, 41089, 41088, 41041, 41140, 40988, 41055, 40926, 41076, 41199, 40842, 41179, 41139, 40988, 41092, 40951, 41065, 40780, 41085, 41034, 41264, 40976, 41072, 40953, 41104, 41343, 40747, 40954, 41084, 41099, 41132, 41123, 41109, 41260, 41016, 41015, 41012, 40827, 40848, 40921, 41068, 40871, 40882, 41139, 40816, 41021, 40952, 40769, 40985, 40980, 41205, 40945, 41140, 41128, 41101, 41120, 40888, 41399, 41057, 40930, 41109, 40945, 40905, 40812, 41269, 41072, 40846, 41061, 41029, 40904, 41109, 41108, 41018, 41019, 41107, 40800, 40855, 40890, 41097, 40970, 41069, 41129, 40863, 40880, 40956, 40980, 40871, 40992, 40916, 40867, 41078, 40829, 40879, 40844, 40942, 40987, 40839, 40970, 41239, 40888, 41081, 40800, 41115, 41339, 40930, 40991, 41123, 41118, 40921, 41067, 40644, 40947, 41172, 40893, 40855, 41094, 40826, 40916, 41015, 41038, 40782, 41121, 40694, 41060, 41130, 40601, 41150, 41091, 40906, 40718, 40982, 41165, 40944, 40985, 40990, 41312, 40830, 40932, 40966, 41121, 41063, 41011, 40884, 40900, 40682, 40974, 40848, 40918, 40978, 40995, 41249, 40986, 40897, 40880, 40839, 40950, 40932, 41086, 40895, 41085, 40884, 40912, 41049, 41013, 40988, 40774, 41213, 41059, 40999, 41020, 41032, 41133, 40828, 41272, 40758, 40859, 40868, 40843, 41111, 40700, 40914, 41056, 40998, 41000, 41078, 40944, 40802, 40839, 40878, 41004, 40943, 40970, 40749, 41047, 41040, 40971, 40987, 40989, 41068, 40979, 41076, 40831, 40994, 40828, 41026, 40892, 40755, 40876, 41009, 41040, 41183, 40927, 40992, 40796, 41199, 40848, 40958, 40771, 40681, 40931, 41002, 41137, 40920, 40945, 40857, 41052, 41035, 40718, 41060, 40819, 40922, 41044, 40866, 40928, 40842, 40677, 41092, 41085, 41031, 40851, 41012, 40850, 41062, 40920, 41012, 41111, 41083, 41136, 40882, 40999, 41129, 41033, 40977, 40866, 40850, 40926, 40882, 41085, 40682, 41205, 41018, 40897, 40746, 40846, 41021, 40818, 40777, 40795, 41069, 40773, 41058, 40862, 40927, 40921, 40748, 40969, 41005, 41005, 40985, 41209, 41142, 40746, 41040, 41252, 41023, 41013, 40932, 40979, 41088, 40790, 40886, 41059, 40847, 40978, 40864, 40832, 40916, 41038, 40980, 41021, 40745, 40909, 41079, 40693, 40797, 40833, 41089, 40943, 41064, 41174, 40904, 41175, 40935, 40823, 40822, 41004, 40754, 41176, 41079, 40944, 40862, 40875, 41141, 41130, 41078, 41122, 40983, 40870, 41047, 41057, 40735, 40933, 41097, 40971, 40951, 40936, 40914, 41158, 41016, 40847, 41063, 40712, 40993, 41027, 40907, 40753, 40811, 40862, 40935, 40950, 40853, 40983, 40820, 40952, 41039, 40752, 41015, 40940, 40987, 41164, 41047, 40900, 40818, 40999, 40827, 40754, 40835, 41010, 41107, 40848, 40902, 40827, 40922, 40735, 40717, 40923, 40947, 40727, 40875, 41017, 41183, 40864, 40740, 40912, 40776, 41127, 40965, 40751, 40888, 41105, 41030, 41047, 40630, 40811, 40697, 40908, 40955, 40943, 40797, 40831, 40859, 41122, 40964, 40861, 41078, 40660, 40949, 41050, 41131, 40898, 40997, 40998, 40765, 41012, 40860, 40821, 40944, 40812, 41035, 40811, 40877, 40887, 40726, 40897, 40776, 40974, 41128, 40872, 40844, 40631, 40768, 40999, 40826, 40940, 40944, 40970, 40821, 40977, 41027, 41079, 41043, 41052, 40796, 40855, 40849, 41137, 40944, 40880, 40697, 40904, 40878, 40925, 40795, 41002, 40689, 40849, 40902, 40700, 40857, 40969, 40910, 41122, 41210, 40810, 41054, 40708, 40843, 40661, 40830, 40980, 41047, 40848, 40940, 40869, 40899, 40866, 40949, 40918, 40905, 40938, 41030, 40964, 40677, 40900, 40814, 40630, 41065, 40899, 40991, 40565, 41017, 40829, 40847, 41079, 40916, 40965, 40945, 40722, 40760, 40785, 40804, 40845, 40978, 40914, 40987, 40859, 41168, 40989, 40873, 40610, 40593, 41060, 41012, 40872, 40941, 41153, 40802, 40868, 40870, 40996, 40808, 40997, 40938, 40928, 40813, 40704, 40981, 40724, 40843, 41009, 40900, 40824, 40932, 41225, 40636, 40880, 40923, 40893, 40861, 40726, 40906, 41024, 41002, 41040, 40779, 40667, 40995, 40785, 40756, 41057, 40806, 40705, 40672, 40930, 40921, 40693, 40905, 40580, 40549, 40856, 40827, 40773, 40653, 40813, 40809, 40780, 40948, 40687, 40740, 40953, 41103, 41161, 40612, 40801, 40853, 40955, 40625, 40987, 41031, 40915, 40891, 40695, 41118, 41043, 41002, 40517, 41043, 40732, 40982, 40904, 41033, 40658, 41091, 40762, 40841, 41025, 40755, 40747, 40823, 40767, 40777, 40875, 40942, 40775, 40783, 40832, 41080, 40934, 40766, 40864, 40486, 40994, 40803, 40781, 40647, 40919, 41068, 40802, 41026, 41134, 40599, 40853, 40808, 40885, 41057, 40835, 40818, 40945, 40887, 40597, 40896, 41190, 40821, 40889, 40822, 40995, 40954, 40890, 41130, 40733, 40922, 40977, 40768, 40978, 40965, 40802, 40949, 40773, 40658, 41021, 40687, 40824, 40796, 40635, 41048, 41000, 40856, 41008, 40919, 40803, 40848, 40610, 40874, 40995, 40841, 40738, 41058, 40799, 40962, 40757, 40748, 40866, 40733, 40669, 41052, 40885, 40888, 41113, 40951, 40844, 40785, 40826, 40991, 40972, 40642, 40886, 40709, 40714, 41030, 40944, 40609, 40744, 40953, 40773, 40733, 40563, 40905, 40792, 40775, 40765, 40960, 40811, 40726, 40876, 40850, 40853, 40977, 40631, 40903, 40849, 40642, 40754, 40862, 41098, 40830, 40737, 40870, 40962, 40790, 40777, 40741, 40642, 40972, 40869, 40900, 40796, 40789, 40862, 40804, 40679, 40732, 40950, 40659, 40773, 40975, 40848, 40619, 40857, 40934, 40747, 40932, 40700, 40876, 40528, 40746, 40616, 40883, 40939, 41060, 40850, 40855, 40848, 40844, 40924, 41175, 40733, 40834, 40948, 40640, 40765, 40589, 40851, 40833, 40944, 40894, 40934, 40732, 40776, 40679, 40923, 40885, 40581, 40780, 40904, 40816, 41023, 40584, 40632, 40962, 40845, 40813, 40483, 41074, 40830, 40615, 40622, 40763, 40998, 40909, 40622, 40895, 40965, 40834, 40960, 40553, 40846, 40767, 40698, 40860, 40719, 40767, 40772, 40759, 41109, 40821, 40776, 40840, 41097, 40876, 40730, 40783, 40843, 40720, 40850, 40745, 40823, 40574, 40692, 40848, 40765, 40839, 40699, 40996, 40837, 40588, 40875, 40790, 40745, 40686, 40982, 40686, 40879, 40654, 40652, 41024, 40910, 40794, 40830, 40944, 41001, 40791, 41055, 40879, 40830, 40887, 40795, 40518, 40635, 41042, 40727, 40999, 40931, 40755, 41076, 40643, 40834, 40768, 40710, 40924, 40779, 40919, 40863, 40757, 40862, 40843, 40878, 40757, 40650, 40677, 40702, 40637, 40769, 40964, 40784, 40597, 40813, 40783, 40626, 40888, 40822, 40773, 40895, 40861, 40736, 40849, 40852, 41028, 40637, 40551, 40685, 40865, 40847, 40949, 40761, 40602, 40604, 40909, 40881, 40762, 40900, 40814, 40795, 40658, 40831, 40932, 40710, 40813, 40889, 40677, 40806, 40889, 40780, 40776, 40724, 40644, 40760, 40698, 41100, 40863, 40855, 40683, 40721, 40989, 40455, 40885, 40705, 40780, 40896, 40668, 40998, 40793, 40700, 40576, 40608, 40880, 40588, 40715, 40663, 40737, 40924, 40934, 40905, 40900, 40921, 40850, 40851, 40841, 40962, 40543, 40963, 40892, 40768, 40640, 40962, 40857, 40768, 40747, 40829, 40740, 40925, 40812, 41018, 41056, 40785, 40873, 40764, 40662, 40943, 40734, 40789, 40667, 40822, 40897, 40610, 40621, 40924, 40533, 40686, 40767, 40672, 40737, 40672, 40616, 40671, 40958, 40810, 40699, 40735, 40802, 40780, 40767, 40845, 40833, 40761, 40519, 40898, 40876, 40641, 40691, 40564, 40811, 40855, 40809, 40849, 40910, 40923, 40575, 40781, 40728, 40687, 41123, 40994, 40697, 40790, 40775, 40705, 40846, 40922, 40978, 40883, 40896, 40561, 41010, 40824, 40736, 40789, 40719, 40531, 40839, 40640, 41138, 40707, 40750, 40783, 40727, 41002, 40822, 40773, 40865, 40924, 40749, 40800, 40764, 40849, 40831, 40796, 40921, 40874, 40838, 41120, 40749, 40827, 40854, 40758, 40628, 40870, 40777, 40842, 40530, 40801, 40948, 40506, 40581, 40643, 40760, 40682, 40642, 40916, 40649, 40869, 40808, 40823, 40757, 40815, 40766, 40578, 40848, 40742, 40712, 40721, 40861, 40642, 40762, 40465, 40725 
};
int d(int n){
  int d = 2;
  int j = 1;
  int div = 0;
  int dis = 0;
  while(d*d<=n){
    if(n%d==0) dis++;
    while(n%d==0){div++; n/=d;}
    d = prime[j++];
  }
  if(n>1) dis++, div++;
  if(dis==div) return div;
  return -1;
}
 
int main(){
  for(int i=2; i<MAXCIUR; i++){
    if(!ciur[i]){
      for(long long d=(long long)i*i; d<MAXCIUR; d+=i)
        ciur[d] = 1;
      prime[primeCnt++] = i;
    }
  }
  fflush(stdout);
  FILE *fout, *fin;
  int a; 
  int b;
  fin = fopen("triprime.in", "r");
  fscanf(fin, "%d %d", &a, &b);
  fclose(fin);
 
  for(int i=1; i<2000; i++) v[i] += v[i-1];
 
  int na = v[a/200000];
  int nb = v[b/200000];
  for(int i = (a/200000*200000); i<a; i++){
    if(d(i)==3) na++;
  }printf("\n");
  for(int i = (b/200000*200000); i<=b; i++){
    if(d(i)==3) nb++;
  }
  // printf("=>%d %d\n", na, nb);
 
  fout = fopen("triprime.out", "w");
  fprintf(fout, "%d", nb-na);
  fclose(fout);
  return 0;
}