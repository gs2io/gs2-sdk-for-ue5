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

#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Domain/Model/BalanceParameterModelMaster.h"
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/CurrentParameterMaster.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/BalanceParameterStatus.h"
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterStatusesByUserIdIteratorPtr FUserDomain::BalanceParameterStatuses(
        const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeBalanceParameterStatusesByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            ParameterName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeBalanceParameterStatuses(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Enchant::Model::FBalanceParameterStatus::TypeName,
            Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "BalanceParameterStatus"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeBalanceParameterStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FBalanceParameterStatus::TypeName,
            Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "BalanceParameterStatus"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain> FUserDomain::BalanceParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FBalanceParameterStatusDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName),
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
        );
    }

    Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterStatusesByUserIdIteratorPtr FUserDomain::RarityParameterStatuses(
        const TOptional<FString> ParameterName
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Iterator::FDescribeRarityParameterStatusesByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            ParameterName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRarityParameterStatuses(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "RarityParameterStatus"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeRarityParameterStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "RarityParameterStatus"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain> FUserDomain::RarityParameterStatus(
        const FString ParameterName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            ParameterName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ParameterName),
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

