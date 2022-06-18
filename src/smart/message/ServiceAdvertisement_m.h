//
// Generated file, do not edit! Created by opp_msgtool 6.0 from smart/message/ServiceAdvertisement.msg.
//

#ifndef __VEINS_SERVICEADVERTISEMENT_M_H
#define __VEINS_SERVICEADVERTISEMENT_M_H

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

class ServiceAdvertisment;

}  // namespace veins

#include "veins/modules/messages/BaseFrame1609_4_m.h" // import veins.modules.messages.BaseFrame1609_4


namespace veins {

/**
 * Class generated from <tt>smart/message/ServiceAdvertisement.msg:30</tt> by opp_msgtool.
 * <pre>
 * packet ServiceAdvertisment extends veins::BaseFrame1609_4
 * {
 *     int targetChannel;
 *     string serviceDescription;
 *     bool rsu;
 *     double rss;
 *     double arrivalTime;
 * }
 * </pre>
 */
class ServiceAdvertisment : public ::veins::BaseFrame1609_4
{
  protected:
    int targetChannel = 0;
    ::omnetpp::opp_string serviceDescription;
    bool rsu = false;
    double rss = 0;
    double arrivalTime = 0;

  private:
    void copy(const ServiceAdvertisment& other);

  protected:
    bool operator==(const ServiceAdvertisment&) = delete;

  public:
    ServiceAdvertisment(const char *name=nullptr, short kind=0);
    ServiceAdvertisment(const ServiceAdvertisment& other);
    virtual ~ServiceAdvertisment();
    ServiceAdvertisment& operator=(const ServiceAdvertisment& other);
    virtual ServiceAdvertisment *dup() const override {return new ServiceAdvertisment(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getTargetChannel() const;
    virtual void setTargetChannel(int targetChannel);

    virtual const char * getServiceDescription() const;
    virtual void setServiceDescription(const char * serviceDescription);

    virtual bool getRsu() const;
    virtual void setRsu(bool rsu);

    virtual double getRss() const;
    virtual void setRss(double rss);

    virtual double getArrivalTime() const;
    virtual void setArrivalTime(double arrivalTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ServiceAdvertisment& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ServiceAdvertisment& obj) {obj.parsimUnpack(b);}


}  // namespace veins


namespace omnetpp {

template<> inline veins::ServiceAdvertisment *fromAnyPtr(any_ptr ptr) { return check_and_cast<veins::ServiceAdvertisment*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __VEINS_SERVICEADVERTISEMENT_M_H

