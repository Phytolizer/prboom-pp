#pragma once
#include <cstdint>
#include <stdexcept>
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
namespace thinker::types
{
class ActionFunction
{
    using m_v_t = void (*)();
    using m_mobj_t = void (*)(mobj_t *);
    using m_player_t = void (*)(player_t *, pspdef_t *);
    using m_vfn_t = void (*)(void *);
    using m_messageThinker_t = void (*)(message_thinker_t *);
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
    m_messageThinker_t m_messageThinker = nullptr;
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
    };
    D m_d = D::undefined;

  public:
    constexpr ActionFunction() = default;
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_v_t v) : m_v(v), m_d(D::v)
    {
    } // ctor(m_v_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_mobj_t mobj) : m_mobj(mobj), m_d(D::mobj)
    {
    } // ctor(m_mobj_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_player_t player)
        : m_player(player), m_d(D::player)
    {
    } // ctor(m_player_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_vfn_t vfn) : m_vfn(vfn), m_d(D::vfn)
    {
    } // ctor(m_vfn_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_messageThinker_t messageThinker)
        : m_messageThinker(messageThinker), m_d(D::message_thinker)
    {
    } // ctor(m_messageThinker_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_ceiling_t ceiling)
        : m_ceiling(ceiling), m_d(D::ceiling)
    {
    } // ctor(m_ceiling_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_vldoor_t vldoor)
        : m_vldoor(vldoor), m_d(D::vldoor)
    {
    } // ctor(m_vldoor_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_plat_t plat) : m_plat(plat), m_d(D::plat)
    {
    } // ctor(m_plat_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_fireflicker_t fireflicker)
        : m_fireflicker(fireflicker), m_d(D::fireflicker)
    {
    } // ctor(m_fireflicker_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_lightflash_t lightflash)
        : m_lightflash(lightflash), m_d(D::lightflash)
    {
    } // ctor(m_lightflash_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_strobe_t strobe)
        : m_strobe(strobe), m_d(D::strobe)
    {
    } // ctor(m_strobe_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_glow_t glow) : m_glow(glow), m_d(D::glow)
    {
    } // ctor(m_glow_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_elevator_t elevator)
        : m_elevator(elevator), m_d(D::elevator)
    {
    } // ctor(m_elevator_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_floormove_t floormove)
        : m_floormove(floormove), m_d(D::floormove)
    {
    } // ctor(m_floormove_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_thinker_t thinker)
        : m_thinker(thinker), m_d(D::thinker)
    {
    } // ctor(m_thinker_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_scroll_t scroll)
        : m_scroll(scroll), m_d(D::scroll)
    {
    } // ctor(m_scroll_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_friction_t friction)
        : m_friction(friction), m_d(D::friction)
    {
    } // ctor(m_friction_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr ActionFunction(m_pusher_t pusher)
        : m_pusher(pusher), m_d(D::pusher)
    {
    } // ctor(m_pusher_t)
    [[nodiscard]] constexpr bool isV()
    {
        return m_d == D::v;
    } // fn isv
    [[nodiscard]] constexpr m_v_t v()
    {
        if (m_d == D::v)
        {
            return m_v;
        }
        throw std::runtime_error{"in 'ActionFunction.hh': This ActionFunction "
                                 "is not a 'm_v_t' (a.k.a 'void (*)()')"};
    } // fn v
    [[nodiscard]] constexpr m_v_t reinterpretV() const
    {
        switch (m_d)
        {
        case D::v:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_v_t (a.k.a. void (*)())"};
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_v_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretV
    void setV()
    {
        m_d = D::v;
    } // setV
    [[nodiscard]] constexpr bool isMobj()
    {
        return m_d == D::mobj;
    } // fn ismobj
    [[nodiscard]] constexpr m_mobj_t mobj()
    {
        if (m_d == D::mobj)
        {
            return m_mobj;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_mobj_t' "
            "(a.k.a 'void (*)(mobj_t*)')"};
    } // fn mobj
    [[nodiscard]] constexpr m_mobj_t reinterpretMobj() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_v);
        case D::mobj:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_mobj_t (a.k.a. void (*)(mobj_t*))"};
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_mobj_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretMobj
    void setMobj()
    {
        m_d = D::mobj;
    } // setMobj
    [[nodiscard]] constexpr bool isPlayer()
    {
        return m_d == D::player;
    } // fn isplayer
    [[nodiscard]] constexpr m_player_t player()
    {
        if (m_d == D::player)
        {
            return m_player;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_player_t' "
            "(a.k.a 'void (*)(player_t*,pspdef_t*)')"};
    } // fn player
    [[nodiscard]] constexpr m_player_t reinterpretPlayer() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_mobj);
        case D::player:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_player_t (a.k.a. void (*)(player_t*,pspdef_t*))"};
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_player_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretPlayer
    void setPlayer()
    {
        m_d = D::player;
    } // setPlayer
    [[nodiscard]] constexpr bool isVfn()
    {
        return m_d == D::vfn;
    } // fn isvfn
    [[nodiscard]] constexpr m_vfn_t vfn()
    {
        if (m_d == D::vfn)
        {
            return m_vfn;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_vfn_t' "
            "(a.k.a 'void (*)(void*)')"};
    } // fn vfn
    [[nodiscard]] constexpr m_vfn_t reinterpretVfn() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_player);
        case D::vfn:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_vfn_t (a.k.a. void (*)(void*))"};
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vfn_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretVfn
    void setVfn()
    {
        m_d = D::vfn;
    } // setVfn
    [[nodiscard]] constexpr bool isMessagethinker()
    {
        return m_d == D::message_thinker;
    } // fn ismessageThinker
    [[nodiscard]] constexpr m_messageThinker_t messageThinker()
    {
        if (m_d == D::message_thinker)
        {
            return m_messageThinker;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_messageThinker_t' (a.k.a 'void (*)(message_thinker_t*)')"};
    } // fn messageThinker
    [[nodiscard]] constexpr m_messageThinker_t reinterpretMessagethinker() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_vfn);
        case D::message_thinker:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_messageThinker_t (a.k.a. void (*)(message_thinker_t*))"};
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_messageThinker_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretMessagethinker
    void setMessagethinker()
    {
        m_d = D::message_thinker;
    } // setMessagethinker
    [[nodiscard]] constexpr bool isCeiling()
    {
        return m_d == D::ceiling;
    } // fn isceiling
    [[nodiscard]] constexpr m_ceiling_t ceiling()
    {
        if (m_d == D::ceiling)
        {
            return m_ceiling;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_ceiling_t' (a.k.a 'void (*)(ceiling_t*)')"};
    } // fn ceiling
    [[nodiscard]] constexpr m_ceiling_t reinterpretCeiling() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_messageThinker);
        case D::ceiling:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_ceiling_t (a.k.a. void (*)(ceiling_t*))"};
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_ceiling_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretCeiling
    void setCeiling()
    {
        m_d = D::ceiling;
    } // setCeiling
    [[nodiscard]] constexpr bool isVldoor()
    {
        return m_d == D::vldoor;
    } // fn isvldoor
    [[nodiscard]] constexpr m_vldoor_t vldoor()
    {
        if (m_d == D::vldoor)
        {
            return m_vldoor;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_vldoor_t' "
            "(a.k.a 'void (*)(vldoor_t*)')"};
    } // fn vldoor
    [[nodiscard]] constexpr m_vldoor_t reinterpretVldoor() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_ceiling);
        case D::vldoor:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_vldoor_t (a.k.a. void (*)(vldoor_t*))"};
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_vldoor_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretVldoor
    void setVldoor()
    {
        m_d = D::vldoor;
    } // setVldoor
    [[nodiscard]] constexpr bool isPlat()
    {
        return m_d == D::plat;
    } // fn isplat
    [[nodiscard]] constexpr m_plat_t plat()
    {
        if (m_d == D::plat)
        {
            return m_plat;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_plat_t' "
            "(a.k.a 'void (*)(plat_t*)')"};
    } // fn plat
    [[nodiscard]] constexpr m_plat_t reinterpretPlat() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_vldoor);
        case D::plat:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_plat_t (a.k.a. void (*)(plat_t*))"};
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_plat_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretPlat
    void setPlat()
    {
        m_d = D::plat;
    } // setPlat
    [[nodiscard]] constexpr bool isFireflicker()
    {
        return m_d == D::fireflicker;
    } // fn isfireflicker
    [[nodiscard]] constexpr m_fireflicker_t fireflicker()
    {
        if (m_d == D::fireflicker)
        {
            return m_fireflicker;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_fireflicker_t' (a.k.a 'void (*)(fireflicker_t*)')"};
    } // fn fireflicker
    [[nodiscard]] constexpr m_fireflicker_t reinterpretFireflicker() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_plat);
        case D::fireflicker:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_fireflicker_t (a.k.a. void (*)(fireflicker_t*))"};
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_fireflicker_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretFireflicker
    void setFireflicker()
    {
        m_d = D::fireflicker;
    } // setFireflicker
    [[nodiscard]] constexpr bool isLightflash()
    {
        return m_d == D::lightflash;
    } // fn islightflash
    [[nodiscard]] constexpr m_lightflash_t lightflash()
    {
        if (m_d == D::lightflash)
        {
            return m_lightflash;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_lightflash_t' (a.k.a 'void (*)(lightflash_t*)')"};
    } // fn lightflash
    [[nodiscard]] constexpr m_lightflash_t reinterpretLightflash() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_fireflicker);
        case D::lightflash:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_lightflash_t (a.k.a. void (*)(lightflash_t*))"};
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_lightflash_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretLightflash
    void setLightflash()
    {
        m_d = D::lightflash;
    } // setLightflash
    [[nodiscard]] constexpr bool isStrobe()
    {
        return m_d == D::strobe;
    } // fn isstrobe
    [[nodiscard]] constexpr m_strobe_t strobe()
    {
        if (m_d == D::strobe)
        {
            return m_strobe;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_strobe_t' "
            "(a.k.a 'void (*)(strobe_t*)')"};
    } // fn strobe
    [[nodiscard]] constexpr m_strobe_t reinterpretStrobe() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_lightflash);
        case D::strobe:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_strobe_t (a.k.a. void (*)(strobe_t*))"};
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_strobe_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretStrobe
    void setStrobe()
    {
        m_d = D::strobe;
    } // setStrobe
    [[nodiscard]] constexpr bool isGlow()
    {
        return m_d == D::glow;
    } // fn isglow
    [[nodiscard]] constexpr m_glow_t glow()
    {
        if (m_d == D::glow)
        {
            return m_glow;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_glow_t' "
            "(a.k.a 'void (*)(glow_t*)')"};
    } // fn glow
    [[nodiscard]] constexpr m_glow_t reinterpretGlow() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_strobe);
        case D::glow:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_glow_t (a.k.a. void (*)(glow_t*))"};
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_glow_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretGlow
    void setGlow()
    {
        m_d = D::glow;
    } // setGlow
    [[nodiscard]] constexpr bool isElevator()
    {
        return m_d == D::elevator;
    } // fn iselevator
    [[nodiscard]] constexpr m_elevator_t elevator()
    {
        if (m_d == D::elevator)
        {
            return m_elevator;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_elevator_t' (a.k.a 'void (*)(elevator_t*)')"};
    } // fn elevator
    [[nodiscard]] constexpr m_elevator_t reinterpretElevator() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_glow);
        case D::elevator:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_elevator_t (a.k.a. void (*)(elevator_t*))"};
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_elevator_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretElevator
    void setElevator()
    {
        m_d = D::elevator;
    } // setElevator
    [[nodiscard]] constexpr bool isFloormove()
    {
        return m_d == D::floormove;
    } // fn isfloormove
    [[nodiscard]] constexpr m_floormove_t floormove()
    {
        if (m_d == D::floormove)
        {
            return m_floormove;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_floormove_t' (a.k.a 'void (*)(floormove_t*)')"};
    } // fn floormove
    [[nodiscard]] constexpr m_floormove_t reinterpretFloormove() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_elevator);
        case D::floormove:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_floormove_t (a.k.a. void (*)(floormove_t*))"};
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_floormove_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretFloormove
    void setFloormove()
    {
        m_d = D::floormove;
    } // setFloormove
    [[nodiscard]] constexpr bool isThinker()
    {
        return m_d == D::thinker;
    } // fn isthinker
    [[nodiscard]] constexpr m_thinker_t thinker()
    {
        if (m_d == D::thinker)
        {
            return m_thinker;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_thinker_t' (a.k.a 'void (*)(thinker_t*)')"};
    } // fn thinker
    [[nodiscard]] constexpr m_thinker_t reinterpretThinker() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_floormove);
        case D::thinker:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_thinker_t (a.k.a. void (*)(thinker_t*))"};
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_thinker_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretThinker
    void setThinker()
    {
        m_d = D::thinker;
    } // setThinker
    [[nodiscard]] constexpr bool isScroll()
    {
        return m_d == D::scroll;
    } // fn isscroll
    [[nodiscard]] constexpr m_scroll_t scroll()
    {
        if (m_d == D::scroll)
        {
            return m_scroll;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_scroll_t' "
            "(a.k.a 'void (*)(scroll_t*)')"};
    } // fn scroll
    [[nodiscard]] constexpr m_scroll_t reinterpretScroll() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_thinker);
        case D::scroll:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_scroll_t (a.k.a. void (*)(scroll_t*))"};
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_friction);
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_scroll_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretScroll
    void setScroll()
    {
        m_d = D::scroll;
    } // setScroll
    [[nodiscard]] constexpr bool isFriction()
    {
        return m_d == D::friction;
    } // fn isfriction
    [[nodiscard]] constexpr m_friction_t friction()
    {
        if (m_d == D::friction)
        {
            return m_friction;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a "
            "'m_friction_t' (a.k.a 'void (*)(friction_t*)')"};
    } // fn friction
    [[nodiscard]] constexpr m_friction_t reinterpretFriction() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_scroll);
        case D::friction:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_friction_t (a.k.a. void (*)(friction_t*))"};
        case D::pusher:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_friction_t>(m_pusher);
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretFriction
    void setFriction()
    {
        m_d = D::friction;
    } // setFriction
    [[nodiscard]] constexpr bool isPusher()
    {
        return m_d == D::pusher;
    } // fn ispusher
    [[nodiscard]] constexpr m_pusher_t pusher()
    {
        if (m_d == D::pusher)
        {
            return m_pusher;
        }
        throw std::runtime_error{
            "in 'ActionFunction.hh': This ActionFunction is not a 'm_pusher_t' "
            "(a.k.a 'void (*)(pusher_t*)')"};
    } // fn pusher
    [[nodiscard]] constexpr m_pusher_t reinterpretPusher() const
    {
        switch (m_d)
        {
        case D::v:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_v);
        case D::mobj:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_mobj);
        case D::player:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_player);
        case D::vfn:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_vfn);
        case D::message_thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_messageThinker);
        case D::ceiling:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_ceiling);
        case D::vldoor:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_vldoor);
        case D::plat:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_plat);
        case D::fireflicker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_fireflicker);
        case D::lightflash:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_lightflash);
        case D::strobe:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_strobe);
        case D::glow:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_glow);
        case D::elevator:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_elevator);
        case D::floormove:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_floormove);
        case D::thinker:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_thinker);
        case D::scroll:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_scroll);
        case D::friction:
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            return reinterpret_cast<m_pusher_t>(m_friction);
        case D::pusher:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is already a "
                "m_pusher_t (a.k.a. void (*)(pusher_t*))"};
        case D::undefined:
            throw std::runtime_error{
                "in 'ActionFunction.hh': This ActionFunction is undefined"};
        } // switch (m_d)
    }     // fn reinterpretPusher
    void setPusher()
    {
        m_d = D::pusher;
    } // setPusher
    [[nodiscard]] constexpr bool isNull() const
    {
        return m_d == D::undefined;
    } // fn isNull
    [[nodiscard]] constexpr bool notNull() const
    {
        return m_d != D::undefined;
    } // fn notNull
    [[nodiscard]] constexpr bool operator==(const ActionFunction &other) const
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
                   m_messageThinker == other.m_messageThinker;
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
            return other.m_d == D::undefined;
        } // switch (m_d)
    }     // fn operator==
    [[nodiscard]] constexpr bool operator!=(const ActionFunction &other) const
    {
        return !(*this == other);
    } // fn operator!=
};
} // namespace thinker::types
