#pragma once
#include <cstdint>
struct pspdef_t;
struct mobj_t;
struct player_t;
struct message_thinker_t;
struct ceiling_t;
struct vldoor_t;
struct plat_t;
struct fireflicker_t;
struct lightflash_t;
struct strobe_t;
struct glow_t;
struct elevator_t;
struct floormove_t;
struct thinker_t;
struct scroll_t;
struct friction_t;
struct pusher_t;
class actionf_t
{
    using m_v_t = void (*)();
    using m_mobj_t = void (*)(mobj_t *);
    using m_player_t = void (*)(player_t *, pspdef_t *);
    using m_vfn_t = void (*)(void *);
    using m_message_thinker_t = void (*)(message_thinker_t *);
    using m_ceiling_t = void (*)(ceiling_t *);
    using m_vldoor_t = void (*)(vldoor_t *);
    using m_plat_t = void (*)(plat_t *);
    using m_fireflicker_t = void (*)(fireflicker_t *);
    using m_lightflash_t = void (*)(lightflash_t *);
    using m_strobe_t = void (*)(strobe_t *);
    using m_glow_t = void (*)(glow_t *);
    using m_elevator_t = void (*)(elevator_t *);
    using m_floormove_t = void (*)(floormove_t *);
    using m_thinker_t = void (*)(thinker_t *);
    using m_scroll_t = void (*)(scroll_t *);
    using m_friction_t = void (*)(friction_t *);
    using m_pusher_t = void (*)(pusher_t *);
    m_v_t m_v = nullptr;
    m_mobj_t m_mobj = nullptr;
    m_player_t m_player = nullptr;
    m_vfn_t m_vfn = nullptr;
    m_message_thinker_t m_message_thinker = nullptr;
    m_ceiling_t m_ceiling = nullptr;
    m_vldoor_t m_vldoor = nullptr;
    m_plat_t m_plat = nullptr;
    m_fireflicker_t m_fireflicker = nullptr;
    m_lightflash_t m_lightflash = nullptr;
    m_strobe_t m_strobe = nullptr;
    m_glow_t m_glow = nullptr;
    m_elevator_t m_elevator = nullptr;
    m_floormove_t m_floormove = nullptr;
    m_thinker_t m_thinker = nullptr;
    m_scroll_t m_scroll = nullptr;
    m_friction_t m_friction = nullptr;
    m_pusher_t m_pusher = nullptr;
    enum class D
    {
        v,
        mobj,
        player,
        vfn,
        message_thinker,
        ceiling,
        vldoor,
        plat,
        fireflicker,
        lightflash,
        strobe,
        glow,
        elevator,
        floormove,
        thinker,
        scroll,
        friction,
        pusher,
        undefined
    } m_d = D::undefined;
  public:
    constexpr actionf_t() = default;
    constexpr actionf_t(m_v_t v) : m_v(v), m_d(D::v)
    {
    }
    constexpr actionf_t(m_mobj_t mobj) : m_mobj(mobj), m_d(D::mobj)
    {
    }
    constexpr actionf_t(m_player_t player) : m_player(player), m_d(D::player)
    {
    }
    constexpr actionf_t(m_vfn_t vfn) : m_vfn(vfn), m_d(D::vfn)
    {
    }
    constexpr actionf_t(m_message_thinker_t message_thinker)
        : m_message_thinker(message_thinker), m_d(D::message_thinker)
    {
    }
    constexpr actionf_t(m_ceiling_t ceiling)
        : m_ceiling(ceiling), m_d(D::ceiling)
    {
    }
    constexpr actionf_t(m_vldoor_t vldoor) : m_vldoor(vldoor), m_d(D::vldoor)
    {
    }
    constexpr actionf_t(m_plat_t plat) : m_plat(plat), m_d(D::plat)
    {
    }
    constexpr actionf_t(m_fireflicker_t fireflicker)
        : m_fireflicker(fireflicker), m_d(D::fireflicker)
    {
    }
    constexpr actionf_t(m_lightflash_t lightflash)
        : m_lightflash(lightflash), m_d(D::lightflash)
    {
    }
    constexpr actionf_t(m_strobe_t strobe) : m_strobe(strobe), m_d(D::strobe)
    {
    }
    constexpr actionf_t(m_glow_t glow) : m_glow(glow), m_d(D::glow)
    {
    }
    constexpr actionf_t(m_elevator_t elevator)
        : m_elevator(elevator), m_d(D::elevator)
    {
    }
    constexpr actionf_t(m_floormove_t floormove)
        : m_floormove(floormove), m_d(D::floormove)
    {
    }
    constexpr actionf_t(m_thinker_t thinker)
        : m_thinker(thinker), m_d(D::thinker)
    {
    }
    constexpr actionf_t(m_scroll_t scroll) : m_scroll(scroll), m_d(D::scroll)
    {
    }
    constexpr actionf_t(m_friction_t friction)
        : m_friction(friction), m_d(D::friction)
    {
    }
    constexpr actionf_t(m_pusher_t pusher) : m_pusher(pusher), m_d(D::pusher)
    {
    }
    m_v_t v()
    {
        switch (m_d)
        {
        case D::v:
            return m_v;
        case D::mobj:
            return reinterpret_cast<m_v_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_v_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_v_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_v_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_v_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_v_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_v_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_v_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_v_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_v_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_v_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_v_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_v_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_v_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_v_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_v_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_v_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_mobj_t mobj()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_mobj_t>(m_v);
        case D::mobj:
            return m_mobj;
        case D::player:
            return reinterpret_cast<m_mobj_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_mobj_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_mobj_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_mobj_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_mobj_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_mobj_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_mobj_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_mobj_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_mobj_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_mobj_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_mobj_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_mobj_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_mobj_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_mobj_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_mobj_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_mobj_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_player_t player()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_player_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_player_t>(m_mobj);
        case D::player:
            return m_player;
        case D::vfn:
            return reinterpret_cast<m_player_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_player_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_player_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_player_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_player_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_player_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_player_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_player_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_player_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_player_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_player_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_player_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_player_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_player_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_player_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_vfn_t vfn()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_vfn_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_vfn_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_vfn_t>(m_player);
        case D::vfn:
            return m_vfn;
        case D::message_thinker:
            return reinterpret_cast<m_vfn_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_vfn_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_vfn_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_vfn_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_vfn_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_vfn_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_vfn_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_vfn_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_vfn_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_vfn_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_vfn_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_vfn_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_vfn_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_vfn_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_message_thinker_t message_thinker()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_message_thinker_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_message_thinker_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_message_thinker_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_message_thinker_t>(m_vfn);
        case D::message_thinker:
            return m_message_thinker;
        case D::ceiling:
            return reinterpret_cast<m_message_thinker_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_message_thinker_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_message_thinker_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_message_thinker_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_message_thinker_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_message_thinker_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_message_thinker_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_message_thinker_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_message_thinker_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_message_thinker_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_message_thinker_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_message_thinker_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_message_thinker_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_ceiling_t ceiling()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_ceiling_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_ceiling_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_ceiling_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_ceiling_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_ceiling_t>(m_message_thinker);
        case D::ceiling:
            return m_ceiling;
        case D::vldoor:
            return reinterpret_cast<m_ceiling_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_ceiling_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_ceiling_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_ceiling_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_ceiling_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_ceiling_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_ceiling_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_ceiling_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_ceiling_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_ceiling_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_ceiling_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_ceiling_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_vldoor_t vldoor()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_vldoor_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_vldoor_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_vldoor_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_vldoor_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_vldoor_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_vldoor_t>(m_ceiling);
        case D::vldoor:
            return m_vldoor;
        case D::plat:
            return reinterpret_cast<m_vldoor_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_vldoor_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_vldoor_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_vldoor_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_vldoor_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_vldoor_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_vldoor_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_vldoor_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_vldoor_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_vldoor_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_vldoor_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_plat_t plat()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_plat_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_plat_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_plat_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_plat_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_plat_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_plat_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_plat_t>(m_vldoor);
        case D::plat:
            return m_plat;
        case D::fireflicker:
            return reinterpret_cast<m_plat_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_plat_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_plat_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_plat_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_plat_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_plat_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_plat_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_plat_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_plat_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_plat_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_fireflicker_t fireflicker()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_fireflicker_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_fireflicker_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_fireflicker_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_fireflicker_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_fireflicker_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_fireflicker_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_fireflicker_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_fireflicker_t>(m_plat);
        case D::fireflicker:
            return m_fireflicker;
        case D::lightflash:
            return reinterpret_cast<m_fireflicker_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_fireflicker_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_fireflicker_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_fireflicker_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_fireflicker_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_fireflicker_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_fireflicker_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_fireflicker_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_fireflicker_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_lightflash_t lightflash()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_lightflash_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_lightflash_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_lightflash_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_lightflash_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_lightflash_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_lightflash_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_lightflash_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_lightflash_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_lightflash_t>(m_fireflicker);
        case D::lightflash:
            return m_lightflash;
        case D::strobe:
            return reinterpret_cast<m_lightflash_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_lightflash_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_lightflash_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_lightflash_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_lightflash_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_lightflash_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_lightflash_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_lightflash_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_strobe_t strobe()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_strobe_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_strobe_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_strobe_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_strobe_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_strobe_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_strobe_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_strobe_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_strobe_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_strobe_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_strobe_t>(m_lightflash);
        case D::strobe:
            return m_strobe;
        case D::glow:
            return reinterpret_cast<m_strobe_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_strobe_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_strobe_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_strobe_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_strobe_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_strobe_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_strobe_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_glow_t glow()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_glow_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_glow_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_glow_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_glow_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_glow_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_glow_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_glow_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_glow_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_glow_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_glow_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_glow_t>(m_strobe);
        case D::glow:
            return m_glow;
        case D::elevator:
            return reinterpret_cast<m_glow_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_glow_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_glow_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_glow_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_glow_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_glow_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_elevator_t elevator()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_elevator_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_elevator_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_elevator_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_elevator_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_elevator_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_elevator_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_elevator_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_elevator_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_elevator_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_elevator_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_elevator_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_elevator_t>(m_glow);
        case D::elevator:
            return m_elevator;
        case D::floormove:
            return reinterpret_cast<m_elevator_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_elevator_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_elevator_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_elevator_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_elevator_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_floormove_t floormove()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_floormove_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_floormove_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_floormove_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_floormove_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_floormove_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_floormove_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_floormove_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_floormove_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_floormove_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_floormove_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_floormove_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_floormove_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_floormove_t>(m_elevator);
        case D::floormove:
            return m_floormove;
        case D::thinker:
            return reinterpret_cast<m_floormove_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_floormove_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_floormove_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_floormove_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_thinker_t thinker()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_thinker_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_thinker_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_thinker_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_thinker_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_thinker_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_thinker_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_thinker_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_thinker_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_thinker_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_thinker_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_thinker_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_thinker_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_thinker_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_thinker_t>(m_floormove);
        case D::thinker:
            return m_thinker;
        case D::scroll:
            return reinterpret_cast<m_thinker_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_thinker_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_thinker_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_scroll_t scroll()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_scroll_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_scroll_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_scroll_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_scroll_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_scroll_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_scroll_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_scroll_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_scroll_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_scroll_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_scroll_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_scroll_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_scroll_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_scroll_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_scroll_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_scroll_t>(m_thinker);
        case D::scroll:
            return m_scroll;
        case D::friction:
            return reinterpret_cast<m_scroll_t>(m_friction);
        case D::pusher:
            return reinterpret_cast<m_scroll_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_friction_t friction()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_friction_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_friction_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_friction_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_friction_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_friction_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_friction_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_friction_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_friction_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_friction_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_friction_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_friction_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_friction_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_friction_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_friction_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_friction_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_friction_t>(m_scroll);
        case D::friction:
            return m_friction;
        case D::pusher:
            return reinterpret_cast<m_friction_t>(m_pusher);
        case D::undefined:
            return nullptr;
        }
    }
    m_pusher_t pusher()
    {
        switch (m_d)
        {
        case D::v:
            return reinterpret_cast<m_pusher_t>(m_v);
        case D::mobj:
            return reinterpret_cast<m_pusher_t>(m_mobj);
        case D::player:
            return reinterpret_cast<m_pusher_t>(m_player);
        case D::vfn:
            return reinterpret_cast<m_pusher_t>(m_vfn);
        case D::message_thinker:
            return reinterpret_cast<m_pusher_t>(m_message_thinker);
        case D::ceiling:
            return reinterpret_cast<m_pusher_t>(m_ceiling);
        case D::vldoor:
            return reinterpret_cast<m_pusher_t>(m_vldoor);
        case D::plat:
            return reinterpret_cast<m_pusher_t>(m_plat);
        case D::fireflicker:
            return reinterpret_cast<m_pusher_t>(m_fireflicker);
        case D::lightflash:
            return reinterpret_cast<m_pusher_t>(m_lightflash);
        case D::strobe:
            return reinterpret_cast<m_pusher_t>(m_strobe);
        case D::glow:
            return reinterpret_cast<m_pusher_t>(m_glow);
        case D::elevator:
            return reinterpret_cast<m_pusher_t>(m_elevator);
        case D::floormove:
            return reinterpret_cast<m_pusher_t>(m_floormove);
        case D::thinker:
            return reinterpret_cast<m_pusher_t>(m_thinker);
        case D::scroll:
            return reinterpret_cast<m_pusher_t>(m_scroll);
        case D::friction:
            return reinterpret_cast<m_pusher_t>(m_friction);
        case D::pusher:
            return m_pusher;
        case D::undefined:
            return nullptr;
        }
    }
    constexpr bool isNull() const
    {
        return m_d == D::undefined;
    }
    constexpr bool notNull() const
    {
        return m_d != D::undefined;
    }
    constexpr bool operator==(const actionf_t &other) const
    {
        switch (m_d)
        {
        case D::v:
            return m_d == other.m_d && m_v == other.m_v;
        case D::mobj:
            return m_d == other.m_d && m_mobj == other.m_mobj;
        case D::player:
            return m_d == other.m_d && m_player == other.m_player;
        case D::vfn:
            return m_d == other.m_d && m_vfn == other.m_vfn;
        case D::message_thinker:
            return m_d == other.m_d &&
                   m_message_thinker == other.m_message_thinker;
        case D::ceiling:
            return m_d == other.m_d && m_ceiling == other.m_ceiling;
        case D::vldoor:
            return m_d == other.m_d && m_vldoor == other.m_vldoor;
        case D::plat:
            return m_d == other.m_d && m_plat == other.m_plat;
        case D::fireflicker:
            return m_d == other.m_d && m_fireflicker == other.m_fireflicker;
        case D::lightflash:
            return m_d == other.m_d && m_lightflash == other.m_lightflash;
        case D::strobe:
            return m_d == other.m_d && m_strobe == other.m_strobe;
        case D::glow:
            return m_d == other.m_d && m_glow == other.m_glow;
        case D::elevator:
            return m_d == other.m_d && m_elevator == other.m_elevator;
        case D::floormove:
            return m_d == other.m_d && m_floormove == other.m_floormove;
        case D::thinker:
            return m_d == other.m_d && m_thinker == other.m_thinker;
        case D::scroll:
            return m_d == other.m_d && m_scroll == other.m_scroll;
        case D::friction:
            return m_d == other.m_d && m_friction == other.m_friction;
        case D::pusher:
            return m_d == other.m_d && m_pusher == other.m_pusher;
        case D::undefined:
            return true;
        }
    }
    constexpr bool operator!=(const actionf_t &other) const
    {
        return !(*this == other);
    }
};