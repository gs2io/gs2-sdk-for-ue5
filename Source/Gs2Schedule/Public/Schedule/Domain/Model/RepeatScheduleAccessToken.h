#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Schedule/Gs2Schedule.h"
#include "Schedule/Model/RepeatSchedule.h"

namespace Gs2::Schedule::Domain { class FGs2ScheduleDomain; typedef TSharedPtr<FGs2ScheduleDomain> FGs2ScheduleDomainPtr; }

namespace Gs2::Schedule::Domain::Model
{
    class GS2SCHEDULE_API FRepeatScheduleAccessTokenDomain : public TSharedFromThis<FRepeatScheduleAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Schedule::Domain::FGs2ScheduleDomainPtr Service;
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client;
        FString ParentKey;
    public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> EventName;
        TOptional<bool> InSchedule;
        TOptional<FString> UserId() const { return AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(); }
        FRepeatScheduleAccessTokenDomain(const Core::Domain::FGs2Ptr&, const Schedule::Domain::FGs2ScheduleDomainPtr&, TOptional<FString>, const Gs2::Auth::Model::FAccessTokenPtr&, TOptional<FString>, TOptional<bool> InSchedule = TOptional<bool>());
        FRepeatScheduleAccessTokenDomain(const FRepeatScheduleAccessTokenDomain& From);
        class GS2SCHEDULE_API FModelTask final : public Core::Util::TGs2Future<Schedule::Model::FRepeatSchedule>, public TSharedFromThis<FModelTask>
        { const TSharedPtr<FRepeatScheduleAccessTokenDomain> Self; public: explicit FModelTask(const TSharedPtr<FRepeatScheduleAccessTokenDomain>& Self); FModelTask(const FModelTask& From); Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Schedule::Model::FRepeatSchedule>> Result) override; };
        friend FModelTask;
        TSharedPtr<FAsyncTask<FModelTask>> Model();
        class GS2SCHEDULE_API FSubscribeWithInitialCallTask final : public Core::Util::TGs2Future<Core::Domain::CallbackID>, public TSharedFromThis<FSubscribeWithInitialCallTask>
        { const TSharedPtr<FRepeatScheduleAccessTokenDomain> Self; const TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback; public: FSubscribeWithInitialCallTask(const TSharedPtr<FRepeatScheduleAccessTokenDomain>&, const TFunction<void(Schedule::Model::FRepeatSchedulePtr)>&); FSubscribeWithInitialCallTask(const FSubscribeWithInitialCallTask&); Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Core::Domain::CallbackID>>) override; };
        friend FSubscribeWithInitialCallTask;
        TSharedPtr<FAsyncTask<FSubscribeWithInitialCallTask>> SubscribeWithInitialCall(TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback);
        Core::Domain::CallbackID Subscribe(TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback);
        void Unsubscribe(Core::Domain::CallbackID CallbackID);
        void Invalidate();
    };
    typedef TSharedPtr<FRepeatScheduleAccessTokenDomain> FRepeatScheduleAccessTokenDomainPtr;
}
