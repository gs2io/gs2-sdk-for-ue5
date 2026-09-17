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
 *
 * 
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Lottery/Domain/Model/ProbabilityAccessToken.h"
#include "Lottery/Model/Cache/Probability.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Domain/Model/LotteryModelMaster.h"
#include "Lottery/Domain/Model/PrizeTableMaster.h"
#include "Lottery/Domain/Model/LotteryModel.h"
#include "Lottery/Domain/Model/PrizeTable.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/LotteryAccessToken.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/ProbabilityAccessToken.h"
#include "Lottery/Domain/Model/CurrentLotteryMaster.h"
#include "Lottery/Domain/Model/PrizeLimit.h"
#include "Lottery/Domain/Model/BoxItems.h"
#include "Lottery/Domain/Model/BoxItemsAccessToken.h"
#include "Lottery/Domain/Model/User.h"
#include "Lottery/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FProbabilityAccessTokenDomain::FProbabilityAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> LotteryName,
        const TOptional<FString> PrizeId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        LotteryName(LotteryName),
        PrizeId(PrizeId)
    {
    }

    FProbabilityAccessTokenDomain::FProbabilityAccessTokenDomain(
        const FProbabilityAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        LotteryName(From.LotteryName),
        PrizeId(From.PrizeId)
    {

    }

    FString FProbabilityAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> LotteryName,
        TOptional<FString> PrizeId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (LotteryName.IsSet() ? *LotteryName : "null") + ":" +
            (PrizeId.IsSet() ? *PrizeId : "null") + ":" +
            ChildType;
    }

    FString FProbabilityAccessTokenDomain::CreateCacheKey(
        TOptional<FString> PrizeId
    )
    {
        return FString("") +
            (PrizeId.IsSet() ? *PrizeId : "null");
    }

    FProbabilityAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FProbabilityAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FProbabilityAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FProbabilityAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FProbability>> Result
    )
    {
        Gs2::Lottery::Model::FProbabilityPtr Value;
        Gs2::Lottery::Model::Cache::FProbabilityCache::TryGet(
            Self->Gs2->Cache,
            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->LotteryName,
            Self->PrizeId,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
            &Value
        );
        *Result = Value;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProbabilityAccessTokenDomain::FModelTask>> FProbabilityAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FProbabilityAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FProbabilityAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FProbabilityAccessTokenDomain> Self,
        const TFunction<void(Gs2::Lottery::Model::FProbabilityPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FProbabilityAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProbabilityAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError()) return Future->GetTask().Error();
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProbabilityAccessTokenDomain::FSubscribeWithInitialCallTask>> FProbabilityAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Lottery::Model::FProbabilityPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FProbabilityAccessTokenDomain::FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FProbabilityAccessTokenDomain::Invalidate()
    {
        const auto SourceToken = AccessToken;
        Gs2::Lottery::Model::Cache::FProbabilityCache::Delete(
            Gs2->Cache,
            NamespaceName,
            SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
            LotteryName,
            PrizeId,
            SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FProbabilityAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Lottery::Model::FProbabilityPtr)> Callback
    )
    {
        const auto SourceToken = AccessToken;
        return Gs2->Cache->Subscribe(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
                NamespaceName,
                SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
                LotteryName,
                SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
            ),
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheKey(PrizeId),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Lottery::Model::FProbability>(obj));
            }
        );
    }

    void FProbabilityAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SourceToken = AccessToken;
        Gs2->Cache->Unsubscribe(
            Gs2::Lottery::Model::FProbability::TypeName,
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheParentKey(
                NamespaceName,
                SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
                LotteryName,
                SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
            ),
            Gs2::Lottery::Model::Cache::FProbabilityCache::CreateCacheKey(PrizeId),
            CallbackID
        );
    }

}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
