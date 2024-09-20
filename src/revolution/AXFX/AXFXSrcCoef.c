#include <revolution/AXFX.h>

extern f32 __SrcTab12khz[128][4];

f32* __AXFXGetSrcCoef(u32 i) {
    return __SrcTab12khz[i];
}

static f32 __SrcTab12khz[128][4] = {
    {0.09750366211f, 0.80221557617f, 0.10159301758f, -0.00097656250f},
    {0.09350585938f, 0.80203247070f, 0.10580444336f, -0.00103759766f},
    {0.08959960938f, 0.80169677734f, 0.11010742188f, -0.00115966797f},
    {0.08578491211f, 0.80117797852f, 0.11447143555f, -0.00128173828f},
    {0.08203125000f, 0.80047607422f, 0.11892700195f, -0.00140380859f},
    {0.07836914062f, 0.79962158203f, 0.12347412109f, -0.00152587891f},
    {0.07479858398f, 0.79861450195f, 0.12814331055f, -0.00164794922f},
    {0.07135009766f, 0.79742431641f, 0.13287353516f, -0.00177001953f},
    {0.06796264648f, 0.79605102539f, 0.13769531250f, -0.00192260742f},
    {0.06469726562f, 0.79452514648f, 0.14260864258f, -0.00204467773f},
    {0.06149291992f, 0.79284667969f, 0.14761352539f, -0.00219726562f},
    {0.05834960938f, 0.79098510742f, 0.15270996094f, -0.00231933594f},
    {0.05532836914f, 0.78894042969f, 0.15789794922f, -0.00247192383f},
    {0.05236816406f, 0.78674316406f, 0.16317749023f, -0.00265502930f},
    {0.04949951172f, 0.78442382812f, 0.16851806641f, -0.00280761719f},
    {0.04672241211f, 0.78189086914f, 0.17398071289f, -0.00299072266f},
    {0.04400634766f, 0.77920532227f, 0.17950439453f, -0.00314331055f},
    {0.04141235352f, 0.77636718750f, 0.18511962891f, -0.00332641602f},
    {0.03887939453f, 0.77337646484f, 0.19082641602f, -0.00350952148f},
    {0.03640747070f, 0.77023315430f, 0.19659423828f, -0.00369262695f},
    {0.03402709961f, 0.76693725586f, 0.20248413086f, -0.00387573242f},
    {0.03173828125f, 0.76348876953f, 0.20843505859f, -0.00405883789f},
    {0.02951049805f, 0.75985717773f, 0.21444702148f, -0.00427246094f},
    {0.02737426758f, 0.75610351562f, 0.22055053711f, -0.00445556641f},
    {0.02529907227f, 0.75219726562f, 0.22674560547f, -0.00466918945f},
    {0.02331542969f, 0.74816894531f, 0.23300170898f, -0.00485229492f},
    {0.02139282227f, 0.74398803711f, 0.23931884766f, -0.00506591797f},
    {0.01956176758f, 0.73965454102f, 0.24572753906f, -0.00531005859f},
    {0.01779174805f, 0.73519897461f, 0.25219726562f, -0.00552368164f},
    {0.01605224609f, 0.73059082031f, 0.25872802734f, -0.00570678711f},
    {0.01440429688f, 0.72586059570f, 0.26535034180f, -0.00592041016f},
    {0.01281738281f, 0.72100830078f, 0.27203369141f, -0.00616455078f},
    {0.01132202148f, 0.71600341797f, 0.27877807617f, -0.00637817383f},
    {0.00988769531f, 0.71090698242f, 0.28558349609f, -0.00656127930f},
    {0.00851440430f, 0.70565795898f, 0.29244995117f, -0.00677490234f},
    {0.00720214844f, 0.70031738281f, 0.29934692383f, -0.00701904297f},
    {0.00592041016f, 0.69485473633f, 0.30633544922f, -0.00723266602f},
    {0.00469970703f, 0.68927001953f, 0.31338500977f, -0.00741577148f},
    {0.00357055664f, 0.68356323242f, 0.32046508789f, -0.00762939453f},
    {0.00247192383f, 0.67773437500f, 0.32760620117f, -0.00787353516f},
    {0.00143432617f, 0.67184448242f, 0.33477783203f, -0.00808715820f},
    {0.00045776367f, 0.66583251953f, 0.34197998047f, -0.00827026367f},
    {-0.00048828125f, 0.65972900391f, 0.34924316406f, -0.00845336914f},
    {-0.00134277344f, 0.65353393555f, 0.35656738281f, -0.00863647461f},
    {-0.00216674805f, 0.64721679688f, 0.36389160156f, -0.00885009766f},
    {-0.00296020508f, 0.64083862305f, 0.37127685547f, -0.00903320312f},
    {-0.00369262695f, 0.63433837891f, 0.37869262695f, -0.00921630859f},
    {-0.00436401367f, 0.62777709961f, 0.38613891602f, -0.00933837891f},
    {-0.00497436523f, 0.62115478516f, 0.39361572266f, -0.00949096680f},
    {-0.00558471680f, 0.61444091797f, 0.40109252930f, -0.00964355469f},
    {-0.00613403320f, 0.60763549805f, 0.40859985352f, -0.00979614258f},
    {-0.00665283203f, 0.60076904297f, 0.41610717773f, -0.00991821289f},
    {-0.00714111328f, 0.59384155273f, 0.42364501953f, -0.01000976562f},
    {-0.00756835938f, 0.58685302734f, 0.43121337891f, -0.01013183594f},
    {-0.00796508789f, 0.57977294922f, 0.43875122070f, -0.01022338867f},
    {-0.00833129883f, 0.57266235352f, 0.44631958008f, -0.01028442383f},
    {-0.00866699219f, 0.56552124023f, 0.45388793945f, -0.01034545898f},
    {-0.00897216797f, 0.55831909180f, 0.46145629883f, -0.01040649414f},
    {-0.00921630859f, 0.55105590820f, 0.46902465820f, -0.01040649414f},
    {-0.00946044922f, 0.54373168945f, 0.47659301758f, -0.01040649414f},
    {-0.00967407227f, 0.53640747070f, 0.48413085938f, -0.01037597656f},
    {-0.00985717773f, 0.52902221680f, 0.49166870117f, -0.01037597656f},
    {-0.01000976562f, 0.52160644531f, 0.49917602539f, -0.01031494141f},
    {-0.01013183594f, 0.51416015625f, 0.50668334961f, -0.01025390625f},
    {-0.01025390625f, 0.50668334961f, 0.51416015625f, -0.01013183594f},
    {-0.01031494141f, 0.49917602539f, 0.52160644531f, -0.01000976562f},
    {-0.01037597656f, 0.49166870117f, 0.52902221680f, -0.00985717773f},
    {-0.01037597656f, 0.48413085938f, 0.53640747070f, -0.00967407227f},
    {-0.01040649414f, 0.47659301758f, 0.54373168945f, -0.00946044922f},
    {-0.01040649414f, 0.46902465820f, 0.55105590820f, -0.00921630859f},
    {-0.01040649414f, 0.46145629883f, 0.55831909180f, -0.00897216797f},
    {-0.01034545898f, 0.45388793945f, 0.56552124023f, -0.00866699219f},
    {-0.01028442383f, 0.44631958008f, 0.57266235352f, -0.00833129883f},
    {-0.01022338867f, 0.43875122070f, 0.57977294922f, -0.00796508789f},
    {-0.01013183594f, 0.43121337891f, 0.58685302734f, -0.00756835938f},
    {-0.01000976562f, 0.42364501953f, 0.59384155273f, -0.00714111328f},
    {-0.00991821289f, 0.41610717773f, 0.60076904297f, -0.00665283203f},
    {-0.00979614258f, 0.40859985352f, 0.60763549805f, -0.00613403320f},
    {-0.00964355469f, 0.40109252930f, 0.61444091797f, -0.00558471680f},
    {-0.00949096680f, 0.39361572266f, 0.62115478516f, -0.00497436523f},
    {-0.00933837891f, 0.38613891602f, 0.62777709961f, -0.00436401367f},
    {-0.00921630859f, 0.37869262695f, 0.63433837891f, -0.00369262695f},
    {-0.00903320312f, 0.37127685547f, 0.64083862305f, -0.00296020508f},
    {-0.00885009766f, 0.36389160156f, 0.64721679688f, -0.00216674805f},
    {-0.00863647461f, 0.35656738281f, 0.65353393555f, -0.00134277344f},
    {-0.00845336914f, 0.34924316406f, 0.65972900391f, -0.00048828125f},
    {-0.00827026367f, 0.34197998047f, 0.66583251953f, 0.00045776367f},
    {-0.00808715820f, 0.33477783203f, 0.67184448242f, 0.00143432617f},
    {-0.00787353516f, 0.32760620117f, 0.67773437500f, 0.00247192383f},
    {-0.00762939453f, 0.32046508789f, 0.68356323242f, 0.00357055664f},
    {-0.00741577148f, 0.31338500977f, 0.68927001953f, 0.00469970703f},
    {-0.00723266602f, 0.30633544922f, 0.69485473633f, 0.00592041016f},
    {-0.00701904297f, 0.29934692383f, 0.70031738281f, 0.00720214844f},
    {-0.00677490234f, 0.29244995117f, 0.70565795898f, 0.00851440430f},
    {-0.00656127930f, 0.28558349609f, 0.71090698242f, 0.00988769531f},
    {-0.00637817383f, 0.27877807617f, 0.71600341797f, 0.01132202148f},
    {-0.00616455078f, 0.27203369141f, 0.72100830078f, 0.01281738281f},
    {-0.00592041016f, 0.26535034180f, 0.72586059570f, 0.01440429688f},
    {-0.00570678711f, 0.25872802734f, 0.73059082031f, 0.01605224609f},
    {-0.00552368164f, 0.25219726562f, 0.73519897461f, 0.01779174805f},
    {-0.00531005859f, 0.24572753906f, 0.73965454102f, 0.01956176758f},
    {-0.00506591797f, 0.23931884766f, 0.74398803711f, 0.02139282227f},
    {-0.00485229492f, 0.23300170898f, 0.74816894531f, 0.02331542969f},
    {-0.00466918945f, 0.22674560547f, 0.75219726562f, 0.02529907227f},
    {-0.00445556641f, 0.22055053711f, 0.75610351562f, 0.02737426758f},
    {-0.00427246094f, 0.21444702148f, 0.75985717773f, 0.02951049805f},
    {-0.00405883789f, 0.20843505859f, 0.76348876953f, 0.03173828125f},
    {-0.00387573242f, 0.20248413086f, 0.76693725586f, 0.03402709961f},
    {-0.00369262695f, 0.19659423828f, 0.77023315430f, 0.03640747070f},
    {-0.00350952148f, 0.19082641602f, 0.77337646484f, 0.03887939453f},
    {-0.00332641602f, 0.18511962891f, 0.77636718750f, 0.04141235352f},
    {-0.00314331055f, 0.17950439453f, 0.77920532227f, 0.04400634766f},
    {-0.00299072266f, 0.17398071289f, 0.78189086914f, 0.04672241211f},
    {-0.00280761719f, 0.16851806641f, 0.78442382812f, 0.04949951172f},
    {-0.00265502930f, 0.16317749023f, 0.78674316406f, 0.05236816406f},
    {-0.00247192383f, 0.15789794922f, 0.78894042969f, 0.05532836914f},
    {-0.00231933594f, 0.15270996094f, 0.79098510742f, 0.05834960938f},
    {-0.00219726562f, 0.14761352539f, 0.79284667969f, 0.06149291992f},
    {-0.00204467773f, 0.14260864258f, 0.79452514648f, 0.06469726562f},
    {-0.00192260742f, 0.13769531250f, 0.79605102539f, 0.06796264648f},
    {-0.00177001953f, 0.13287353516f, 0.79742431641f, 0.07135009766f},
    {-0.00164794922f, 0.12814331055f, 0.79861450195f, 0.07479858398f},
    {-0.00152587891f, 0.12347412109f, 0.79962158203f, 0.07836914062f},
    {-0.00140380859f, 0.11892700195f, 0.80047607422f, 0.08203125000f},
    {-0.00128173828f, 0.11447143555f, 0.80117797852f, 0.08578491211f},
    {-0.00115966797f, 0.11010742188f, 0.80169677734f, 0.08959960938f},
    {-0.00103759766f, 0.10580444336f, 0.80203247070f, 0.09350585938f},
    {-0.00097656250f, 0.10159301758f, 0.80221557617f, 0.09750366211f}};
