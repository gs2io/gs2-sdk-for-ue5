#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Model/Gs2Error.h"
#include "Schedule/Model/RepeatSchedule.h"

namespace Gs2::Schedule::Model::Cache
{
    class GS2SCHEDULE_API FRepeatScheduleCache final
    {
    public:
        static FString CreateCacheParentKey(TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<int32> TimeOffset = TOptional<int32>());
        static FString CreateCacheKey(TOptional<FString> EventName);
        static bool TryGet(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<FString> EventName, TOptional<int32> TimeOffset, Gs2::Schedule::Model::FRepeatSchedulePtr* Out);
        static void Put(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<FString> EventName, TOptional<int32> TimeOffset, const Gs2::Schedule::Model::FRepeatSchedulePtr& Item);
        static void Delete(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<FString> EventName, TOptional<int32> TimeOffset);
        static Gs2::Core::Model::FGs2ErrorPtr Fetch(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<FString> EventName, TOptional<int32> TimeOffset, const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Schedule::Model::FRepeatSchedulePtr*)>& FetchImpl, Gs2::Schedule::Model::FRepeatSchedulePtr* Out);
        static Gs2::Core::Domain::CallbackID ListSubscribe(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<int32> TimeOffset, TFunction<void(TArray<Gs2::Schedule::Model::FRepeatSchedulePtr>)> Callback);
        static void ListUnsubscribe(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<int32> TimeOffset, Gs2::Core::Domain::CallbackID CallbackID);
    };
}
