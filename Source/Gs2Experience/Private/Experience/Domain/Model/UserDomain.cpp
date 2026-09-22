/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/Namespace.h"
#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/CurrentExperienceMaster.h"
#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/StatusAccessToken.h"
#include "Experience/Model/Cache/Status.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Experience::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Experience::Domain::Iterator::FDescribeStatusesByUserIdIteratorPtr FUserDomain::Statuses(
        const TOptional<FString> ExperienceName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Experience::Domain::Iterator::FDescribeStatusesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            ExperienceName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeStatuses(
    TFunction<void()> Callback, const TOptional<FString> ExperienceName
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Experience::Model::FStatus::TypeName,
            Gs2::Experience::Model::Cache::FStatusCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeStatuses(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> ExperienceName, const TOptional<FString> TimeOffsetToken
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Experience::Model::FStatus::TypeName,
            Gs2::Experience::Model::Cache::FStatusCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectStatusesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Experience::Model::FStatusPtr>>, public TSharedFromThis<FCollectStatusesTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Experience::Model::FStatusPtr>)> OnCollected;
    const TOptional<FString> QueryExperienceName;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectStatusesTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Experience::Model::FStatusPtr>)> OnCollected,const TOptional<FString> ExperienceName,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryExperienceName(ExperienceName), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectStatusesTask(const FCollectStatusesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryExperienceName(From.QueryExperienceName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Experience::Model::FStatusPtr>>> Result) override
        {
            TArray<Gs2::Experience::Model::FStatusPtr> Items;
            auto Iterator = Self->Statuses(QueryExperienceName, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Experience::Model::FStatusPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeStatuses(
        TFunction<void(TArray<Gs2::Experience::Model::FStatusPtr>)> Callback,const TOptional<FString> ExperienceName,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Experience::Domain::FGs2ExperienceDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryExperienceName = ExperienceName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Experience::Model::Cache::FStatusCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Experience::Model::FStatus::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Experience::Model::FStatusPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Experience::Model::FStatus>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryExperienceName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStatusesTask>>(Domain, Callback, QueryExperienceName, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateStatuses(const TOptional<FString> ExperienceName,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Experience::Model::FStatus::TypeName,
            Gs2::Experience::Model::Cache::FStatusCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeStatusesWithInitialCallTask::FSubscribeStatusesWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Experience::Model::FStatusPtr>)> Callback,const TOptional<FString> ExperienceName,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryExperienceName(ExperienceName), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeStatusesWithInitialCallTask::FSubscribeStatusesWithInitialCallTask(const FSubscribeStatusesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryExperienceName(From.QueryExperienceName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeStatusesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStatusesTask>>(Self, TFunction<void(TArray<Gs2::Experience::Model::FStatusPtr>)>(), QueryExperienceName, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStatuses(Callback, QueryExperienceName, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeStatusesWithInitialCallTask>> FUserDomain::SubscribeStatusesWithInitialCall(TFunction<void(TArray<Gs2::Experience::Model::FStatusPtr>)> Callback,const TOptional<FString> ExperienceName,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStatusesWithInitialCallTask>>(this->AsShared(), Callback, ExperienceName, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Experience::Domain::Model::FStatusDomain> FUserDomain::Status(
        const FString ExperienceName,
        const FString PropertyId
    )
    {
        return MakeShared<Gs2::Experience::Domain::Model::FStatusDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            ExperienceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ExperienceName),
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
