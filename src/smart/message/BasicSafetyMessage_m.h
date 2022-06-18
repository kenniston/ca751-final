//
// Generated file, do not edit! Created by opp_msgtool 6.0 from smart/message/BasicSafetyMessage.msg.
//

#ifndef __VEINS_BASICSAFETYMESSAGE_M_H
#define __VEINS_BASICSAFETYMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif


namespace veins {

class BasicSafetyMessage;

}  // namespace veins

#include "veins/base/utils/Coord_m.h" // import veins.base.utils.Coord

#include "veins/base/utils/SimpleAddress_m.h" // import veins.base.utils.SimpleAddress

#include "veins/modules/messages/BaseFrame1609_4_m.h" // import veins.modules.messages.BaseFrame1609_4


namespace veins {

/**
 * Class generated from <tt>smart/message/BasicSafetyMessage.msg:32</tt> by opp_msgtool.
 * <pre>
 * class BasicSafetyMessage extends BaseFrame1609_4
 * {
 *     LAddress::L2Type senderId;
 *     Coord senderPos;
 *     Coord senderSpeed;
 *     Coord senderHeading;
 *     Coord senderGpsPos;
 *     double senderAccel;
 *     double senderWidth;
 *     double senderLength;
 *     int senderType;
 *     int senderAttackType;
 *     unsigned long senderPseudonym;
 *     bool rsu;
 *     double rss;
 *     double arrivalTime;
 *     double lastDistanceTraveled;
 * }
 * </pre>
 */
class BasicSafetyMessage : public ::veins::BaseFrame1609_4
{
  protected:
    LAddress::L2Type senderId;
    Coord senderPos;
    Coord senderSpeed;
    Coord senderHeading;
    Coord senderGpsPos;
    double senderAccel = 0;
    double senderWidth = 0;
    double senderLength = 0;
    int senderType = 0;
    int senderAttackType = 0;
    unsigned long senderPseudonym = 0;
    bool rsu = false;
    double rss = 0;
    double arrivalTime = 0;
    double lastDistanceTraveled = 0;

  private:
    void copy(const BasicSafetyMessage& other);

  protected:
    bool operator==(const BasicSafetyMessage&) = delete;

  public:
    BasicSafetyMessage(const char *name=nullptr);
    BasicSafetyMessage(const BasicSafetyMessage& other);
    virtual ~BasicSafetyMessage();
    BasicSafetyMessage& operator=(const BasicSafetyMessage& other);
    virtual BasicSafetyMessage *dup() const override {return new BasicSafetyMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const LAddress::L2Type& getSenderId() const;
    virtual LAddress::L2Type& getSenderIdForUpdate() { return const_cast<LAddress::L2Type&>(const_cast<BasicSafetyMessage*>(this)->getSenderId());}
    virtual void setSenderId(const LAddress::L2Type& senderId);

    virtual const Coord& getSenderPos() const;
    virtual Coord& getSenderPosForUpdate() { return const_cast<Coord&>(const_cast<BasicSafetyMessage*>(this)->getSenderPos());}
    virtual void setSenderPos(const Coord& senderPos);

    virtual const Coord& getSenderSpeed() const;
    virtual Coord& getSenderSpeedForUpdate() { return const_cast<Coord&>(const_cast<BasicSafetyMessage*>(this)->getSenderSpeed());}
    virtual void setSenderSpeed(const Coord& senderSpeed);

    virtual const Coord& getSenderHeading() const;
    virtual Coord& getSenderHeadingForUpdate() { return const_cast<Coord&>(const_cast<BasicSafetyMessage*>(this)->getSenderHeading());}
    virtual void setSenderHeading(const Coord& senderHeading);

    virtual const Coord& getSenderGpsPos() const;
    virtual Coord& getSenderGpsPosForUpdate() { return const_cast<Coord&>(const_cast<BasicSafetyMessage*>(this)->getSenderGpsPos());}
    virtual void setSenderGpsPos(const Coord& senderGpsPos);

    virtual double getSenderAccel() const;
    virtual void setSenderAccel(double senderAccel);

    virtual double getSenderWidth() const;
    virtual void setSenderWidth(double senderWidth);

    virtual double getSenderLength() const;
    virtual void setSenderLength(double senderLength);

    virtual int getSenderType() const;
    virtual void setSenderType(int senderType);

    virtual int getSenderAttackType() const;
    virtual void setSenderAttackType(int senderAttackType);

    virtual unsigned long getSenderPseudonym() const;
    virtual void setSenderPseudonym(unsigned long senderPseudonym);

    virtual bool getRsu() const;
    virtual void setRsu(bool rsu);

    virtual double getRss() const;
    virtual void setRss(double rss);

    virtual double getArrivalTime() const;
    virtual void setArrivalTime(double arrivalTime);

    virtual double getLastDistanceTraveled() const;
    virtual void setLastDistanceTraveled(double lastDistanceTraveled);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BasicSafetyMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BasicSafetyMessage& obj) {obj.parsimUnpack(b);}


}  // namespace veins


namespace omnetpp {

template<> inline veins::BasicSafetyMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<veins::BasicSafetyMessage*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __VEINS_BASICSAFETYMESSAGE_M_H

