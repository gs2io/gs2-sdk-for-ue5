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
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Account::Domain::Model
{

    FAccountAccessTokenDomain::FAccountAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Account"
        ))
    {
    }

    FAccountAccessTokenDomain::FAccountAccessTokenDomain(
        const FAccountAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Account::Domain::Iterator::FDescribeTakeOversIteratorPtr FAccountAccessTokenDomain::TakeOvers(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FAccountAccessTokenDomain::SubscribeTakeOvers(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "TakeOver"
            ),
            Callback
        );
    }

    void FAccountAccessTokenDomain::UnsubscribeTakeOvers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "TakeOver"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain> FAccountAccessTokenDomain::TakeOver(
        const int32 Type
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            Type
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerAccessTokenDomain> FAccountAccessTokenDomain::DataOwner(
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FDataOwnerAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    FString FAccountAccessTokenDomain::CreateCacheParentKey(
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

    FString FAccountAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }

    FAccountAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FAccountAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FAccountAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAccountAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FAccount>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FAccount> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FAccount>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                Self->UserId()
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccountAccessTokenDomain::FModelTask>> FAccountAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAccountAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAccountAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FAccountPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FAccount::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                UserId()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FAccount>(obj));
            }
        );
    }

    void FAccountAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FAccount::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                UserId()
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

