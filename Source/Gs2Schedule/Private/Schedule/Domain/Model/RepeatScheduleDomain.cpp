#include "Schedule/Domain/Model/RepeatSchedule.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Model/Cache/RepeatSchedule.h"
#include "Schedule/Request/GetEventByUserIdRequest.h"

namespace Gs2::Schedule::Domain::Model
{
    using Gs2::Schedule::Model::Cache::FRepeatScheduleCache;
    FRepeatScheduleDomain::FRepeatScheduleDomain(const Core::Domain::FGs2Ptr& Gs2, const Schedule::Domain::FGs2ScheduleDomainPtr& Service, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<FString> EventName, TOptional<bool> InSchedule):
        Gs2(Gs2), Service(Service), Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)), ParentKey(Gs2::Schedule::Model::Cache::FRepeatScheduleCache::CreateCacheParentKey(NamespaceName, UserId, InSchedule.Get(true), TOptional<int32>())), NamespaceName(NamespaceName), UserId(UserId), EventName(EventName), InSchedule(InSchedule) {}
    FRepeatScheduleDomain::FRepeatScheduleDomain(const FRepeatScheduleDomain& From): Gs2(From.Gs2), Service(From.Service), Client(From.Client), ParentKey(From.ParentKey), NamespaceName(From.NamespaceName), UserId(From.UserId), EventName(From.EventName), InSchedule(From.InSchedule) {}
    FRepeatScheduleDomain::FModelTask::FModelTask(const TSharedPtr<FRepeatScheduleDomain>& Self): Self(Self) {}
    FRepeatScheduleDomain::FModelTask::FModelTask(const FModelTask& From): TGs2Future(From), Self(From.Self) {}
    Gs2::Core::Model::FGs2ErrorPtr FRepeatScheduleDomain::FModelTask::Action(TSharedPtr<TSharedPtr<Schedule::Model::FRepeatSchedule>> Result)
    {
        const auto Parent = FRepeatScheduleCache::CreateCacheParentKey(Self->NamespaceName, Self->UserId, Self->InSchedule.Get(true), TOptional<int32>());
        const auto Key = FRepeatScheduleCache::CreateCacheKey(Self->EventName);
        return Self->Gs2->Cache->ExecuteWithKeyLock(Schedule::Model::FRepeatSchedule::TypeName, Parent, Key, [this, Result]() {
            Schedule::Model::FRepeatSchedulePtr Value;
            if (FRepeatScheduleCache::TryGet(Self->Gs2->Cache, Self->NamespaceName, Self->UserId, Self->InSchedule.Get(true), Self->EventName, TOptional<int32>(), &Value)) { *Result = Value; return Gs2::Core::Model::FGs2ErrorPtr(); }
            const auto Error = FRepeatScheduleCache::Fetch(Self->Gs2->Cache, Self->NamespaceName, Self->UserId, Self->InSchedule.Get(true), Self->EventName, TOptional<int32>(), [Self = Self](Schedule::Model::FRepeatSchedulePtr* Out) {
                const auto Request = MakeShared<Schedule::Request::FGetEventByUserIdRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithEventName(Self->EventName)
                    ->WithUserId(Self->UserId)
                    ->WithIsInSchedule(Self->InSchedule);
                const auto Future = Self->Client->GetEventByUserId(Request); Future->StartSynchronousTask(); if (Future->GetTask().IsError()) { const auto Error = Future->GetTask().Error(); Future->EnsureCompletion(); return Error; } const auto Event = Future->GetTask().Result(); Future->EnsureCompletion(); *Out = Event.IsValid() ? Event->GetRepeatSchedule() : nullptr; return Gs2::Core::Model::FGs2ErrorPtr();
            }, &Value);
            if (Error.IsValid()) return Error;
            *Result = Value;
            return Gs2::Core::Model::FGs2ErrorPtr();
        });
    }
    TSharedPtr<FAsyncTask<FRepeatScheduleDomain::FModelTask>> FRepeatScheduleDomain::Model() { return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared()); }
    FRepeatScheduleDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(const TSharedPtr<FRepeatScheduleDomain>& Self, const TFunction<void(Schedule::Model::FRepeatSchedulePtr)>& Callback): Self(Self), Callback(Callback) {}
    FRepeatScheduleDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(const FSubscribeWithInitialCallTask& From): TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FRepeatScheduleDomain::FSubscribeWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    { const auto Future = Self->Model(); Future->StartSynchronousTask(); Future->EnsureCompletion(); if (Future->GetTask().IsError()) return Future->GetTask().Error(); const auto Item = Future->GetTask().Result(); const auto Id = Self->Subscribe(Callback); Callback(Item); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(Id); return nullptr; }
    TSharedPtr<FAsyncTask<FRepeatScheduleDomain::FSubscribeWithInitialCallTask>> FRepeatScheduleDomain::SubscribeWithInitialCall(TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback) { return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback); }
    Gs2::Core::Domain::CallbackID FRepeatScheduleDomain::Subscribe(TFunction<void(Schedule::Model::FRepeatSchedulePtr)> Callback)
    {
        const auto Parent = FRepeatScheduleCache::CreateCacheParentKey(NamespaceName, UserId, InSchedule.Get(true), TOptional<int32>()); const auto Key = FRepeatScheduleCache::CreateCacheKey(EventName); const TWeakPtr<FRepeatScheduleDomain> WeakSelf = AsShared();
        return Gs2->Cache->Subscribe(Schedule::Model::FRepeatSchedule::TypeName, Parent, Key, [Callback](TSharedPtr<FGs2Object> Object){ Callback(StaticCastSharedPtr<Schedule::Model::FRepeatSchedule>(Object)); }, [WeakSelf](){ const auto Self = WeakSelf.Pin(); if (Self.IsValid()) { const auto Task = Self->Model(); Task->StartBackgroundTask(); } });
    }
    void FRepeatScheduleDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackID) { Gs2->Cache->Unsubscribe(Schedule::Model::FRepeatSchedule::TypeName, FRepeatScheduleCache::CreateCacheParentKey(NamespaceName, UserId, InSchedule.Get(true), TOptional<int32>()), FRepeatScheduleCache::CreateCacheKey(EventName), CallbackID); }
    void FRepeatScheduleDomain::Invalidate() { FRepeatScheduleCache::Delete(Gs2->Cache, NamespaceName, UserId, EventName, TOptional<int32>()); }
}
