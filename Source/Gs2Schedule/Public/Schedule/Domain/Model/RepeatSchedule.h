#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Schedule/Gs2Schedule.h"
#include "Schedule/Model/RepeatSchedule.h"

namespace Gs2::Schedule::Domain { class FGs2ScheduleDomain; typedef TSharedPtr<FGs2ScheduleDomain> FGs2ScheduleDomainPtr; }

namespace Gs2::Schedule::Domain::Model
{
    class GS2SCHEDULE_API FRepeatScheduleDomain : public TSharedFromThis<FRepeatScheduleDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Schedule::Domain::FGs2ScheduleDomainPtr Service;
        const Gs2::Schedule::FGs2ScheduleRestClientPtr Client;
        FString ParentKey;
    public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> EventName;
        TOptional<bool> InSchedule;
        FRepeatScheduleDomain(const Core::Domain::FGs2Ptr&, const Schedule::Domain::FGs2ScheduleDomainPtr&, TOptional<FString>, TOptional<FString>, TOptional<FString>, TOptional<bool> InSchedule = TOptional<bool>());
        FRepeatScheduleDomain(const FRepeatScheduleDomain& From);
        class GS2SCHEDULE_API FModelTask final : public Core::Util::TGs2Future<Schedule::Model::FRepeatSchedule>, public TSharedFromThis<FModelTask>
        { const TSharedPtr<FRepeatScheduleDomain> Self; public: explicit FModelTask(const TSharedPtr<FRepeatScheduleDomain>& Self); FModelTask(const FModelTask& From); Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Schedule::Model::FRepeatSchedule>> Result) override; };
        friend FModelTask;
        TSharedPtr<FAsyncTask<FModelTask>> Model();
        class GS2SCHEDULE_API FSubscribeWithInitialCallTask final : public Core::Util::TGs2Future<Core::Domain::CallbackID>, public TSharedFromThis<FSubscribeWithInitialCallTask>
        { const TSharedPtr<FRepeatScheduleDomain> Self; const TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback; public: FSubscribeWithInitialCallTask(const TSharedPtr<FRepeatScheduleDomain>&, const TFunction<void(Schedule::Model::FRepeatSchedulePtr)>&); FSubscribeWithInitialCallTask(const FSubscribeWithInitialCallTask&); Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Core::Domain::CallbackID>>) override; };
        friend FSubscribeWithInitialCallTask;
        TSharedPtr<FAsyncTask<FSubscribeWithInitialCallTask>> SubscribeWithInitialCall(TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback);
        Core::Domain::CallbackID Subscribe(TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback);
        void Unsubscribe(Core::Domain::CallbackID CallbackID);
        void Invalidate();
    };
    typedef TSharedPtr<FRepeatScheduleDomain> FRepeatScheduleDomainPtr;
}
