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

#include "Inbox/Domain/Model/ReceivedAccessToken.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/ReceivedAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FReceivedAccessTokenDomain::FReceivedAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Received"
        ))
    {
    }

    FReceivedAccessTokenDomain::FReceivedAccessTokenDomain(
        const FReceivedAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FString FReceivedAccessTokenDomain::CreateCacheParentKey(
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

    FString FReceivedAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FReceivedAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceivedAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FReceivedAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FReceived>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inbox::Model::FReceived> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inbox::Model::FReceived>(
            Self->ParentKey,
            Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedAccessTokenDomain::FModelTask>> FReceivedAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceivedAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FReceivedAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Inbox::Model::FReceivedPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inbox::Model::FReceived::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inbox::Model::FReceived>(obj));
            }
        );
    }

    void FReceivedAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inbox::Model::FReceived::TypeName,
            ParentKey,
            Gs2::Inbox::Domain::Model::FReceivedDomain::CreateCacheKey(
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

