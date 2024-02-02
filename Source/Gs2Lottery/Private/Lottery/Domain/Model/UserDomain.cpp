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

#include "Lottery/Domain/Model/User.h"
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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    TSharedPtr<Gs2::Lottery::Domain::Model::FLotteryDomain> FUserDomain::Lottery(
        const FString LotteryName
    )
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FLotteryDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            LotteryName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LotteryName)
        );
    }

    Gs2::Lottery::Domain::Iterator::FDescribeBoxesByUserIdIteratorPtr FUserDomain::Boxes(
    ) const
    {
        return MakeShared<Gs2::Lottery::Domain::Iterator::FDescribeBoxesByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeBoxes(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "BoxItems"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeBoxes(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Lottery::Model::FBoxItems::TypeName,
            Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "BoxItems"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Lottery::Domain::Model::FBoxItemsDomain> FUserDomain::BoxItems(
        const FString PrizeTableName
    )
    {
        return MakeShared<Gs2::Lottery::Domain::Model::FBoxItemsDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            PrizeTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(PrizeTableName)
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

