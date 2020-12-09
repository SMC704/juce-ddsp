//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  randn.cpp
//
//  Code generation for function 'randn'
//


// Include files
#include "randn.h"
#include "DDSPSynth_data.h"
#include "eml_rand_mt19937ar.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder
{
  void randn(double r[4096])
  {
    static const double dv[257] = { 0.0, 0.215241895984875, 0.286174591792068,
      0.335737519214422, 0.375121332878378, 0.408389134611989, 0.43751840220787,
      0.46363433679088, 0.487443966139235, 0.50942332960209, 0.529909720661557,
      0.549151702327164, 0.567338257053817, 0.584616766106378, 0.601104617755991,
      0.61689699000775, 0.63207223638606, 0.646695714894993, 0.660822574244419,
      0.674499822837293, 0.687767892795788, 0.700661841106814, 0.713212285190975,
      0.725446140909999, 0.737387211434295, 0.749056662017815, 0.760473406430107,
      0.771654424224568, 0.782615023307232, 0.793369058840623, 0.80392911698997,
      0.814306670135215, 0.824512208752291, 0.834555354086381, 0.844444954909153,
      0.854189171008163, 0.863795545553308, 0.87327106808886, 0.882622229585165,
      0.891855070732941, 0.900975224461221, 0.909987953496718, 0.91889818364959,
      0.927710533401999, 0.936429340286575, 0.945058684468165, 0.953602409881086,
      0.96206414322304, 0.970447311064224, 0.978755155294224, 0.986990747099062,
      0.99515699963509, 1.00325667954467, 1.01129241744, 1.01926671746548,
      1.02718196603564, 1.03504043983344, 1.04284431314415, 1.05059566459093,
      1.05829648333067, 1.06594867476212, 1.07355406579244, 1.0811144097034,
      1.08863139065398, 1.09610662785202, 1.10354167942464, 1.11093804601357,
      1.11829717411934, 1.12562045921553, 1.13290924865253, 1.14016484436815,
      1.14738850542085, 1.15458145035993, 1.16174485944561, 1.16887987673083,
      1.17598761201545, 1.18306914268269, 1.19012551542669, 1.19715774787944,
      1.20416683014438, 1.2111537262437, 1.21811937548548, 1.22506469375653,
      1.23199057474614, 1.23889789110569, 1.24578749554863, 1.2526602218949,
      1.25951688606371, 1.26635828701823, 1.27318520766536, 1.27999841571382,
      1.28679866449324, 1.29358669373695, 1.30036323033084, 1.30712898903073,
      1.31388467315022, 1.32063097522106, 1.32736857762793, 1.33409815321936,
      1.3408203658964, 1.34753587118059, 1.35424531676263, 1.36094934303328,
      1.36764858359748, 1.37434366577317, 1.38103521107586, 1.38772383568998,
      1.39441015092814, 1.40109476367925, 1.4077782768464, 1.41446128977547,
      1.42114439867531, 1.42782819703026, 1.43451327600589, 1.44120022484872,
      1.44788963128058, 1.45458208188841, 1.46127816251028, 1.46797845861808,
      1.47468355569786, 1.48139403962819, 1.48811049705745, 1.49483351578049,
      1.50156368511546, 1.50830159628131, 1.51504784277671, 1.521803020761,
      1.52856772943771, 1.53534257144151, 1.542128153229, 1.54892508547417,
      1.55573398346918, 1.56255546753104, 1.56939016341512, 1.57623870273591,
      1.58310172339603, 1.58997987002419, 1.59687379442279, 1.60378415602609,
      1.61071162236983, 1.61765686957301, 1.62462058283303, 1.63160345693487,
      1.63860619677555, 1.64562951790478, 1.65267414708306, 1.65974082285818,
      1.66683029616166, 1.67394333092612, 1.68108070472517, 1.68824320943719,
      1.69543165193456, 1.70264685479992, 1.7098896570713, 1.71716091501782,
      1.72446150294804, 1.73179231405296, 1.73915426128591, 1.74654827828172,
      1.75397532031767, 1.76143636531891, 1.76893241491127, 1.77646449552452,
      1.78403365954944, 1.79164098655216, 1.79928758454972, 1.80697459135082,
      1.81470317596628, 1.82247454009388, 1.83028991968276, 1.83815058658281,
      1.84605785028518, 1.8540130597602, 1.86201760539967, 1.87007292107127,
      1.878180486293, 1.88634182853678, 1.8945585256707, 1.90283220855043,
      1.91116456377125, 1.91955733659319, 1.92801233405266, 1.93653142827569,
      1.94511656000868, 1.95376974238465, 1.96249306494436, 1.97128869793366,
      1.98015889690048, 1.98910600761744, 1.99813247135842, 2.00724083056053,
      2.0164337349062, 2.02571394786385, 2.03508435372962, 2.04454796521753,
      2.05410793165065, 2.06376754781173, 2.07353026351874, 2.0833996939983,
      2.09337963113879, 2.10347405571488, 2.11368715068665, 2.12402331568952,
      2.13448718284602, 2.14508363404789, 2.15581781987674, 2.16669518035431,
      2.17772146774029, 2.18890277162636, 2.20024554661128, 2.21175664288416,
      2.22344334009251, 2.23531338492992, 2.24737503294739, 2.25963709517379,
      2.27210899022838, 2.28480080272449, 2.29772334890286, 2.31088825060137,
      2.32430801887113, 2.33799614879653, 2.35196722737914, 2.36623705671729,
      2.38082279517208, 2.39574311978193, 2.41101841390112, 2.42667098493715,
      2.44272531820036, 2.4592083743347, 2.47614993967052, 2.49358304127105,
      2.51154444162669, 2.53007523215985, 2.54922155032478, 2.56903545268184,
      2.58957598670829, 2.61091051848882, 2.63311639363158, 2.65628303757674,
      2.68051464328574, 2.70593365612306, 2.73268535904401, 2.76094400527999,
      2.79092117400193, 2.82287739682644, 2.85713873087322, 2.89412105361341,
      2.93436686720889, 2.97860327988184, 3.02783779176959, 3.08352613200214,
      3.147889289518, 3.2245750520478, 3.32024473383983, 3.44927829856143,
      3.65415288536101, 3.91075795952492 };

    static const double dv1[257] = { 1.0, 0.977101701267673, 0.959879091800108,
      0.9451989534423, 0.932060075959231, 0.919991505039348, 0.908726440052131,
      0.898095921898344, 0.887984660755834, 0.878309655808918, 0.869008688036857,
      0.860033621196332, 0.851346258458678, 0.842915653112205, 0.834716292986884,
      0.826726833946222, 0.818929191603703, 0.811307874312656, 0.803849483170964,
      0.796542330422959, 0.789376143566025, 0.782341832654803, 0.775431304981187,
      0.768637315798486, 0.761953346836795, 0.755373506507096, 0.748892447219157,
      0.742505296340151, 0.736207598126863, 0.729995264561476, 0.72386453346863,
      0.717811932630722, 0.711834248878248, 0.705928501332754, 0.700091918136512,
      0.694321916126117, 0.688616083004672, 0.682972161644995, 0.677388036218774,
      0.671861719897082, 0.66639134390875, 0.660975147776663, 0.655611470579697,
      0.650298743110817, 0.645035480820822, 0.639820277453057, 0.634651799287624,
      0.629528779924837, 0.624450015547027, 0.619414360605834, 0.614420723888914,
      0.609468064925773, 0.604555390697468, 0.599681752619125, 0.594846243767987,
      0.590047996332826, 0.585286179263371, 0.580559996100791, 0.575868682972354,
      0.571211506735253, 0.566587763256165, 0.561996775814525, 0.557437893618766,
      0.552910490425833, 0.548413963255266, 0.543947731190026, 0.539511234256952,
      0.535103932380458, 0.530725304403662, 0.526374847171684, 0.522052074672322,
      0.517756517229756, 0.513487720747327, 0.509245245995748, 0.505028667943468,
      0.500837575126149, 0.49667156905249, 0.492530263643869, 0.488413284705458,
      0.484320269426683, 0.480250865909047, 0.476204732719506, 0.47218153846773,
      0.468180961405694, 0.464202689048174, 0.460246417812843, 0.456311852678716,
      0.452398706861849, 0.448506701507203, 0.444635565395739, 0.440785034665804,
      0.436954852547985, 0.433144769112652, 0.429354541029442, 0.425583931338022,
      0.421832709229496, 0.418100649837848, 0.414387534040891, 0.410693148270188,
      0.407017284329473, 0.403359739221114, 0.399720314980197, 0.396098818515832,
      0.392495061459315, 0.388908860018789, 0.385340034840077, 0.381788410873393,
      0.378253817245619, 0.374736087137891, 0.371235057668239, 0.367750569779032,
      0.364282468129004, 0.360830600989648, 0.357394820145781, 0.353974980800077,
      0.350570941481406, 0.347182563956794, 0.343809713146851, 0.340452257044522,
      0.337110066637006, 0.333783015830718, 0.330470981379163, 0.327173842813601,
      0.323891482376391, 0.320623784956905, 0.317370638029914, 0.314131931596337,
      0.310907558126286, 0.307697412504292, 0.30450139197665, 0.301319396100803,
      0.298151326696685, 0.294997087799962, 0.291856585617095, 0.288729728482183,
      0.285616426815502, 0.282516593083708, 0.279430141761638, 0.276356989295668,
      0.273297054068577, 0.270250256365875, 0.267216518343561, 0.264195763997261,
      0.261187919132721, 0.258192911337619, 0.255210669954662, 0.252241126055942,
      0.249284212418529, 0.246339863501264, 0.24340801542275, 0.240488605940501,
      0.237581574431238, 0.23468686187233, 0.231804410824339, 0.228934165414681,
      0.226076071322381, 0.223230075763918, 0.220396127480152, 0.217574176724331,
      0.214764175251174, 0.211966076307031, 0.209179834621125, 0.206405406397881,
      0.203642749310335, 0.200891822494657, 0.198152586545776, 0.195425003514135,
      0.192709036903589, 0.190004651670465, 0.187311814223801, 0.1846304924268,
      0.181960655599523, 0.179302274522848, 0.176655321443735, 0.174019770081839,
      0.171395595637506, 0.168782774801212, 0.166181285764482, 0.163591108232366,
      0.161012223437511, 0.158444614155925, 0.15588826472448, 0.153343161060263,
      0.150809290681846, 0.148286642732575, 0.145775208005994, 0.143274978973514,
      0.140785949814445, 0.138308116448551, 0.135841476571254, 0.133386029691669,
      0.130941777173644, 0.12850872228, 0.126086870220186, 0.123676228201597,
      0.12127680548479, 0.11888861344291, 0.116511665625611, 0.114145977827839,
      0.111791568163838, 0.109448457146812, 0.107116667774684, 0.104796225622487,
      0.102487158941935, 0.10018949876881, 0.0979032790388625, 0.095628536713009,
      0.093365311912691, 0.0911136480663738, 0.0888735920682759,
      0.0866451944505581, 0.0844285095703535, 0.082223595813203,
      0.0800305158146631, 0.0778493367020961, 0.0756801303589272,
      0.0735229737139814, 0.0713779490588905, 0.0692451443970068,
      0.0671246538277886, 0.065016577971243, 0.0629210244377582,
      0.06083810834954, 0.0587679529209339, 0.0567106901062031,
      0.0546664613248891, 0.0526354182767924, 0.0506177238609479,
      0.0486135532158687, 0.0466230949019305, 0.0446465522512946,
      0.0426841449164746, 0.0407361106559411, 0.0388027074045262,
      0.0368842156885674, 0.0349809414617162, 0.0330932194585786,
      0.0312214171919203, 0.0293659397581334, 0.0275272356696031,
      0.0257058040085489, 0.0239022033057959, 0.0221170627073089,
      0.0203510962300445, 0.0186051212757247, 0.0168800831525432,
      0.0151770883079353, 0.0134974506017399, 0.0118427578579079,
      0.0102149714397015, 0.00861658276939875, 0.00705087547137324,
      0.00552240329925101, 0.00403797259336304, 0.00260907274610216,
      0.0012602859304986, 0.000477467764609386 };

    unsigned int u[2];
    for (int k = 0; k < 4096; k++) {
      double b_r;
      int exitg1;
      int i;
      do {
        exitg1 = 0;
        genrand_uint32_vector(state, u);
        i = static_cast<int>((u[1] >> 24U) + 1U);
        b_r = ((static_cast<double>(u[0] >> 3U) * 1.6777216E+7 + static_cast<
                double>(static_cast<int>(u[1]) & 16777215)) *
               2.2204460492503131E-16 - 1.0) * dv[i];
        if (std::abs(b_r) <= dv[i - 1]) {
          exitg1 = 1;
        } else if (i < 256) {
          double b_u;

          // ========================= COPYRIGHT NOTICE ============================ 
          //  This is a uniform (0,1) pseudorandom number generator based on:        
          //                                                                         
          //  A C-program for MT19937, with initialization improved 2002/1/26.       
          //  Coded by Takuji Nishimura and Makoto Matsumoto.                        
          //                                                                         
          //  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,      
          //  All rights reserved.                                                   
          //                                                                         
          //  Redistribution and use in source and binary forms, with or without     
          //  modification, are permitted provided that the following conditions     
          //  are met:                                                               
          //                                                                         
          //    1. Redistributions of source code must retain the above copyright    
          //       notice, this list of conditions and the following disclaimer.     
          //                                                                         
          //    2. Redistributions in binary form must reproduce the above copyright 
          //       notice, this list of conditions and the following disclaimer      
          //       in the documentation and/or other materials provided with the     
          //       distribution.                                                     
          //                                                                         
          //    3. The names of its contributors may not be used to endorse or       
          //       promote products derived from this software without specific      
          //       prior written permission.                                         
          //                                                                         
          //  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    
          //  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      
          //  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  
          //  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT  
          //  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
          //  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       
          //  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  
          //  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  
          //  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    
          //  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
          //  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
          //                                                                         
          // =============================   END   ================================= 
          do {
            genrand_uint32_vector(state, u);
            u[0] >>= 5U;
            u[1] >>= 6U;
            b_u = 1.1102230246251565E-16 * (static_cast<double>(u[0]) *
              6.7108864E+7 + static_cast<double>(u[1]));
          } while (b_u == 0.0);

          if (dv1[i] + b_u * (dv1[i - 1] - dv1[i]) < std::exp(-0.5 * b_r * b_r))
          {
            exitg1 = 1;
          }
        } else {
          double b_u;
          double x;
          do {
            // ========================= COPYRIGHT NOTICE ============================ 
            //  This is a uniform (0,1) pseudorandom number generator based on:        
            //                                                                         
            //  A C-program for MT19937, with initialization improved 2002/1/26.       
            //  Coded by Takuji Nishimura and Makoto Matsumoto.                        
            //                                                                         
            //  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,      
            //  All rights reserved.                                                   
            //                                                                         
            //  Redistribution and use in source and binary forms, with or without     
            //  modification, are permitted provided that the following conditions     
            //  are met:                                                               
            //                                                                         
            //    1. Redistributions of source code must retain the above copyright    
            //       notice, this list of conditions and the following disclaimer.     
            //                                                                         
            //    2. Redistributions in binary form must reproduce the above copyright 
            //       notice, this list of conditions and the following disclaimer      
            //       in the documentation and/or other materials provided with the     
            //       distribution.                                                     
            //                                                                         
            //    3. The names of its contributors may not be used to endorse or       
            //       promote products derived from this software without specific      
            //       prior written permission.                                         
            //                                                                         
            //  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    
            //  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      
            //  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  
            //  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT  
            //  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
            //  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       
            //  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  
            //  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  
            //  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    
            //  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
            //  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
            //                                                                         
            // =============================   END   ================================= 
            do {
              genrand_uint32_vector(state, u);
              u[0] >>= 5U;
              u[1] >>= 6U;
              b_u = 1.1102230246251565E-16 * (static_cast<double>(u[0]) *
                6.7108864E+7 + static_cast<double>(u[1]));
            } while (b_u == 0.0);

            x = std::log(b_u) * 0.273661237329758;

            // ========================= COPYRIGHT NOTICE ============================ 
            //  This is a uniform (0,1) pseudorandom number generator based on:        
            //                                                                         
            //  A C-program for MT19937, with initialization improved 2002/1/26.       
            //  Coded by Takuji Nishimura and Makoto Matsumoto.                        
            //                                                                         
            //  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,      
            //  All rights reserved.                                                   
            //                                                                         
            //  Redistribution and use in source and binary forms, with or without     
            //  modification, are permitted provided that the following conditions     
            //  are met:                                                               
            //                                                                         
            //    1. Redistributions of source code must retain the above copyright    
            //       notice, this list of conditions and the following disclaimer.     
            //                                                                         
            //    2. Redistributions in binary form must reproduce the above copyright 
            //       notice, this list of conditions and the following disclaimer      
            //       in the documentation and/or other materials provided with the     
            //       distribution.                                                     
            //                                                                         
            //    3. The names of its contributors may not be used to endorse or       
            //       promote products derived from this software without specific      
            //       prior written permission.                                         
            //                                                                         
            //  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    
            //  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      
            //  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  
            //  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT  
            //  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  
            //  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       
            //  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  
            //  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  
            //  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    
            //  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
            //  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
            //                                                                         
            // =============================   END   ================================= 
            do {
              genrand_uint32_vector(state, u);
              u[0] >>= 5U;
              u[1] >>= 6U;
              b_u = 1.1102230246251565E-16 * (static_cast<double>(u[0]) *
                6.7108864E+7 + static_cast<double>(u[1]));
            } while (b_u == 0.0);
          } while (!(-2.0 * std::log(b_u) > x * x));

          if (b_r < 0.0) {
            b_r = x - 3.65415288536101;
          } else {
            b_r = 3.65415288536101 - x;
          }

          exitg1 = 1;
        }
      } while (exitg1 == 0);

      r[k] = b_r;
    }
  }
}

// End of code generation (randn.cpp)
