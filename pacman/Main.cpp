਍⌀椀昀 开䐀䔀䈀唀䜀ഀ
// ReSharper disable once CppUnusedIncludeDirective਍⌀椀昀 开开栀愀猀开椀渀挀氀甀搀攀⠀㰀瘀氀搀⸀栀㸀⤀ഀ
#endif਍⌀攀渀搀椀昀ഀ
਍⌀椀渀挀氀甀搀攀 㰀匀䐀䰀⸀栀㸀ഀ
਍⌀椀渀挀氀甀搀攀 ∀䴀椀渀椀最椀渀⸀栀∀ഀ
#include "SceneManager.h"਍⌀椀渀挀氀甀搀攀 ∀䘀倀匀䌀愀氀挀䌀漀洀瀀漀渀攀渀琀⸀栀∀ഀ
਍ഀ
#include "SceneFactory.h"਍⌀椀渀挀氀甀搀攀 ∀匀挀攀渀攀䤀搀⸀栀∀ഀ
#include "ServiceLocator.h"਍⌀椀渀挀氀甀搀攀 ∀匀攀琀琀椀渀最猀⸀栀∀ഀ
#include "Sound.h"਍ഀ
using namespace dae;਍ഀ
void Load()਍笀ഀ
	//Initialize sound system਍ऀ匀攀爀瘀椀挀攀䰀漀挀愀琀漀爀㨀㨀刀攀最椀猀琀攀爀匀漀甀渀搀匀礀猀琀攀洀⠀猀琀搀㨀㨀洀愀欀攀开猀栀愀爀攀搀㰀氀漀最最椀渀最开猀漀甀渀搀开猀礀猀琀攀洀㸀⠀猀琀搀㨀㨀洀愀欀攀开猀栀愀爀攀搀㰀匀䐀䰀匀漀甀渀搀匀礀猀琀攀洀㸀⠀⤀⤀⤀㬀ഀ
	ServiceLocator::GetSoundSystem().InitializeSoundSystem();਍ऀ匀攀爀瘀椀挀攀䰀漀挀愀琀漀爀㨀㨀䜀攀琀匀漀甀渀搀匀礀猀琀攀洀⠀⤀⸀刀攀最椀猀琀攀爀匀漀甀渀搀⠀匀漀甀渀搀㨀㨀䈀䔀䜀䤀一一䤀一䜀Ⰰ ∀⸀⸀⼀䐀愀琀愀⼀瀀愀挀洀愀渀开戀攀最椀渀渀椀渀最⸀眀愀瘀∀⤀㬀ഀ
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::PACMAN_CHOMP, "../Data/munch_1.wav");਍ऀ匀攀爀瘀椀挀攀䰀漀挀愀琀漀爀㨀㨀䜀攀琀匀漀甀渀搀匀礀猀琀攀洀⠀⤀⸀刀攀最椀猀琀攀爀匀漀甀渀搀⠀匀漀甀渀搀㨀㨀䐀䔀䄀吀䠀Ⰰ ∀⸀⸀⼀䐀愀琀愀⼀瀀愀挀洀愀渀开搀攀愀琀栀⸀眀愀瘀∀⤀㬀ഀ
	ServiceLocator::GetSoundSystem().RegisterSound(Sound::EATGHOST, "../Data/pacman_eatghost.wav");਍ऀ匀攀爀瘀椀挀攀䰀漀挀愀琀漀爀㨀㨀䜀攀琀匀漀甀渀搀匀礀猀琀攀洀⠀⤀⸀刀攀最椀猀琀攀爀匀漀甀渀搀⠀匀漀甀渀搀㨀㨀倀䄀䌀䴀䄀一开倀伀圀䔀刀唀倀Ⰰ ∀⸀⸀⼀䐀愀琀愀⼀瀀漀眀攀爀开瀀攀氀氀攀琀⸀眀愀瘀∀⤀㬀ഀ
਍ഀ
	//Load first scene਍ऀ匀挀攀渀攀䘀愀挀琀漀爀礀㨀㨀䜀攀琀䤀渀猀琀愀渀挀攀⠀⤀⸀䰀漀愀搀䴀愀椀渀䴀攀渀甀匀挀攀渀攀⠀⤀㬀ഀ
਍ऀ⼀⼀䤀渀猀琀爀甀挀琀椀漀渀猀ഀ
	std::cout << "\n\nCONTROLS \n\n";਍ഀ
	std::cout << "Keyboard: \n";਍ऀ猀琀搀㨀㨀挀漀甀琀 㰀㰀 ∀ⴀⴀⴀⴀⴀⴀⴀⴀⴀ 尀渀∀㬀ഀ
	std::cout << "WASD   : Move pacman \n";਍ऀ猀琀搀㨀㨀挀漀甀琀 㰀㰀 ∀愀爀爀漀眀猀 㨀 䴀漀瘀攀 瀀愀挀洀愀渀 尀渀尀渀∀㬀ഀ
਍ऀ猀琀搀㨀㨀挀漀甀琀 㰀㰀 ∀䌀漀渀琀爀漀氀氀攀爀猀㨀 尀渀∀㬀 ഀ
	std::cout << "------------ \n"; ਍ऀ猀琀搀㨀㨀挀漀甀琀 㰀㰀 ∀洀漀瘀攀 瀀愀挀洀愀渀  㨀 昀椀爀猀琀 挀漀渀琀爀漀氀氀攀爀Ⰰ 戀甀琀琀漀渀猀 愀渀搀 氀攀昀琀 琀栀甀洀戀Ⰰ 攀砀挀攀瀀琀 搀甀愀氀 瀀氀愀礀攀爀 洀漀搀攀 愀渀搀 漀渀氀礀 ㄀ 挀漀渀琀爀漀氀氀攀爀 愀瘀愀椀氀愀戀氀攀 尀渀∀㬀ഀ
	std::cout << "second player: last controller, buttons and left thumb\n\n";਍ഀ
	std::cout << "Sound : \n";਍ऀ猀琀搀㨀㨀挀漀甀琀 㰀㰀 ∀ⴀⴀⴀⴀⴀⴀⴀ 尀渀∀㬀ഀ
	std::cout << "M      : Toggle sound ON/OFF\n\n";਍ഀ
	std::cout << "General (debugging) : \n";਍ऀ猀琀搀㨀㨀挀漀甀琀 㰀㰀 ∀ⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀⴀ 尀渀∀㬀ഀ
	std::cout << "<F8>   : Move to next level (in game only)\n";਍ऀ猀琀搀㨀㨀挀漀甀琀 㰀㰀 ∀㰀䘀㤀㸀   㨀 䴀漀瘀攀 琀漀 倀爀攀瘀椀漀甀猀 匀挀攀渀攀 ⠀洀愀椀渀 洀攀渀甀 㰀ⴀ 最愀洀攀 戀漀愀爀搀 㰀ⴀ 栀椀最栀 猀挀漀爀攀猀⤀尀渀∀㬀ഀ
	std::cout << "<F10>  : Move to Next Scene (main menu -> game board -> high scores)\n";਍紀ഀ
਍⼀⼀ 氀攀瘀攀氀 氀漀愀搀攀爀ഀ
// 1 wall  2 pickupsmall   3 powerup    4 empty tile     5 gate      6 spawn ghost      7 spawn pacman਍ഀ
int main(int, char* []) {਍ऀ䴀椀渀椀最椀渀 攀渀最椀渀攀⠀∀倀愀挀洀愀渀∀Ⰰ 匀攀琀琀椀渀最猀㨀㨀䄀瀀瀀圀椀搀琀栀Ⰰ 匀攀琀琀椀渀最猀㨀㨀䄀瀀瀀䠀攀椀最栀琀Ⰰ ∀⸀⸀⼀䐀愀琀愀⼀∀⤀㬀ഀ
	engine.Run(Load);਍ऀ爀攀琀甀爀渀 　㬀ഀ
}਍�