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

#include "News/Domain/Model/SetCookieRequestEntryAccessToken.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/SetCookieRequestEntryAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::News::Domain::Model
{

    FSetCookieRequestEntryAccessTokenDomain::FSetCookieRequestEntryAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> Key,
        const TOptional<FString> Value
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        Key(Key),
        Value(Value),
        ParentKey(Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "SetCookieRequestEntry"
        ))
    {
    }

    FSetCookieRequestEntryAccessTokenDomain::FSetCookieRequestEntryAccessTokenDomain(
        const FSetCookieRequestEntryAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FString FSetCookieRequestEntryAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> Key,
        TOptional<FString> Value,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Key.IsSet() ? *Key : "null") + ":" +
            (Value.IsSet() ? *Value : "null") + ":" +
            ChildType;
    }

    FString FSetCookieRequestEntryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> Key,
        TOptional<FString> Value
    )
    {
        return FString() +
            (Key.IsSet() ? *Key : "null") + ":" + 
            (Value.IsSet() ? *Value : "null");
    }

    FSetCookieRequestEntryAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSetCookieRequestEntryAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSetCookieRequestEntryAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetCookieRequestEntryAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FSetCookieRequestEntry>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::News::Model::FSetCookieRequestEntry> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::News::Model::FSetCookieRequestEntry>(
            Self->ParentKey,
            Gs2::News::Domain::Model::FSetCookieRequestEntryDomain::CreateCacheKey(
                Self->Key,
                Self->Value
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSetCookieRequestEntryAccessTokenDomain::FModelTask>> FSetCookieRequestEntryAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSetCookieRequestEntryAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

