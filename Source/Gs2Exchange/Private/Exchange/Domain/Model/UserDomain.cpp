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

#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"
#include "Exchange/Model/Cache/RateModel.h"
#include "Exchange/Model/Cache/IncrementalRateModel.h"
#include "Exchange/Model/Cache/Await.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    FUserDomain::FCreateAwaitTask::FCreateAwaitTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FCreateAwaitByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateAwaitTask::FCreateAwaitTask(
        const FCreateAwaitTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateAwaitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CreateAwaitByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Exchange::Model::Cache::FAwaitCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Exchange::Domain::Model::FAwaitDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCreateAwaitTask>> FUserDomain::CreateAwait(
        Request::FCreateAwaitByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateAwaitTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeDomain> FUserDomain::Exchange(
    )
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FExchangeDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId
        );
    }

    Gs2::Exchange::Domain::Iterator::FDescribeAwaitsByUserIdIteratorPtr FUserDomain::Awaits(
        const TOptional<FString> RateName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RateName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeAwaits(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Exchange::Model::FAwait::TypeName,
            Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeAwaits(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Exchange::Model::FAwait::TypeName,
            Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectAwaitsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Exchange::Model::FAwaitPtr>>, public TSharedFromThis<FCollectAwaitsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> OnCollected;
    const TOptional<FString> QueryRateName;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectAwaitsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> OnCollected,const TOptional<FString> RateName,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryRateName(RateName), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectAwaitsTask(const FCollectAwaitsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryRateName(From.QueryRateName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Exchange::Model::FAwaitPtr>>> Result) override
        {
            TArray<Gs2::Exchange::Model::FAwaitPtr> Items;
            auto Iterator = Self->Awaits(QueryRateName, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Exchange::Model::FAwaitPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeAwaits(
        TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> Callback,const TOptional<FString> RateName,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Exchange::Domain::FGs2ExchangeDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryRateName = RateName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Exchange::Model::FAwait::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Exchange::Model::FAwaitPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Exchange::Model::FAwait>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryRateName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAwaitsTask>>(Domain, Callback, QueryRateName, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateAwaits(const TOptional<FString> RateName,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Exchange::Model::FAwait::TypeName,
            Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeAwaitsWithInitialCallTask::FSubscribeAwaitsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> Callback,const TOptional<FString> RateName,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryRateName(RateName), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeAwaitsWithInitialCallTask::FSubscribeAwaitsWithInitialCallTask(const FSubscribeAwaitsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryRateName(From.QueryRateName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeAwaitsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAwaitsTask>>(Self, TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)>(), QueryRateName, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeAwaits(Callback, QueryRateName, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeAwaitsWithInitialCallTask>> FUserDomain::SubscribeAwaitsWithInitialCall(TFunction<void(TArray<Gs2::Exchange::Model::FAwaitPtr>)> Callback,const TOptional<FString> RateName,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAwaitsWithInitialCallTask>>(this->AsShared(), Callback, RateName, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain> FUserDomain::Await(
        const FString AwaitName
    )
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FAwaitDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            AwaitName == TEXT("") ? TOptional<FString>() : TOptional<FString>(AwaitName)
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
