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

#include "AdReward/Domain/Model/HistoryAccessToken.h"
#include "AdReward/Domain/Model/History.h"
#include "AdReward/Domain/Model/Namespace.h"
#include "AdReward/Domain/Model/User.h"
#include "AdReward/Domain/Model/UserAccessToken.h"
#include "AdReward/Domain/Model/Point.h"
#include "AdReward/Domain/Model/PointAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::AdReward::Domain::Model
{

    FHistoryAccessTokenDomain::FHistoryAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> TransactionId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::AdReward::FGs2AdRewardRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        TransactionId(TransactionId),
        ParentKey(Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "History"
        ))
    {
    }

    FHistoryAccessTokenDomain::FHistoryAccessTokenDomain(
        const FHistoryAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        TransactionId(From.TransactionId),
        ParentKey(From.ParentKey)
    {

    }

    FString FHistoryAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TransactionId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TransactionId.IsSet() ? *TransactionId : "null") + ":" +
            ChildType;
    }

    FString FHistoryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TransactionId
    )
    {
        return FString("") +
            (TransactionId.IsSet() ? *TransactionId : "null");
    }

    FHistoryAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FHistoryAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FHistoryAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FHistoryAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FHistory>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::AdReward::Model::FHistory> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::AdReward::Model::FHistory>(
            Self->ParentKey,
            Gs2::AdReward::Domain::Model::FHistoryDomain::CreateCacheKey(
                Self->TransactionId
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FHistoryAccessTokenDomain::FModelTask>> FHistoryAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FHistoryAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FHistoryAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::AdReward::Model::FHistoryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::AdReward::Model::FHistory::TypeName,
            ParentKey,
            Gs2::AdReward::Domain::Model::FHistoryDomain::CreateCacheKey(
                TransactionId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::AdReward::Model::FHistory>(obj));
            }
        );
    }

    void FHistoryAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::AdReward::Model::FHistory::TypeName,
            ParentKey,
            Gs2::AdReward::Domain::Model::FHistoryDomain::CreateCacheKey(
                TransactionId
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

