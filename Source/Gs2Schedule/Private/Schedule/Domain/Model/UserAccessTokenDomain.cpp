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

#include "Schedule/Domain/Model/UserAccessToken.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Schedule::Domain::Iterator::FDescribeTriggersIteratorPtr FUserAccessTokenDomain::Triggers(
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Iterator::FDescribeTriggersIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeTriggers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Trigger"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeTriggers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Trigger"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomain> FUserAccessTokenDomain::Trigger(
        const FString TriggerName
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Model::FTriggerAccessTokenDomain>(
            Gs2,
            NamespaceName,
            AccessToken,
            TriggerName == TEXT("") ? TOptional<FString>() : TOptional<FString>(TriggerName)
        );
    }

    Gs2::Schedule::Domain::Iterator::FDescribeEventsIteratorPtr FUserAccessTokenDomain::Events(
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Iterator::FDescribeEventsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeEvents(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
            Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Event"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeEvents(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
            Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Event"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Schedule::Domain::Model::FEventAccessTokenDomain> FUserAccessTokenDomain::Event(
        const FString EventName
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Model::FEventAccessTokenDomain>(
            Gs2,
            NamespaceName,
            AccessToken,
            EventName == TEXT("") ? TOptional<FString>() : TOptional<FString>(EventName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
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

    FString FUserAccessTokenDomain::CreateCacheKey(
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

