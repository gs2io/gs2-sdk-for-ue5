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

#include "Dictionary/Domain/Model/LikeAccessToken.h"
#include "Dictionary/Domain/Model/Like.h"
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/EntryModelMaster.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/Like.h"
#include "Dictionary/Domain/Model/LikeAccessToken.h"
#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Dictionary::Domain::Model
{

    FLikeAccessTokenDomain::FLikeAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> EntryModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        EntryModelName(EntryModelName),
        ParentKey(Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Like"
        ))
    {
    }

    FLikeAccessTokenDomain::FLikeAccessTokenDomain(
        const FLikeAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        EntryModelName(From.EntryModelName),
        ParentKey(From.ParentKey)
    {

    }

    FLikeAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FLikeAccessTokenDomain>& Self,
        const Request::FGetLikeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLikeAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLikeAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FLike>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithEntryModelName(Self->EntryModelName);
        const auto Future = Self->Client->GetLike(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLikeAccessTokenDomain::FGetTask>> FLikeAccessTokenDomain::Get(
        Request::FGetLikeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLikeAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> EntryModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (EntryModelName.IsSet() ? *EntryModelName : "null") + ":" +
            ChildType;
    }

    FString FLikeAccessTokenDomain::CreateCacheKey(
        TOptional<FString> EntryModelName
    )
    {
        return FString("") +
            (EntryModelName.IsSet() ? *EntryModelName : "null");
    }

    FLikeAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FLikeAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FLikeAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLikeAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FLike>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Dictionary::Model::FLike> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Dictionary::Model::FLike>(
            Self->ParentKey,
            Gs2::Dictionary::Domain::Model::FLikeDomain::CreateCacheKey(
                Self->EntryModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Dictionary::Request::FGetLikeRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Dictionary::Domain::Model::FLikeDomain::CreateCacheKey(
                    Self->EntryModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Dictionary::Model::FLike::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "like")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Dictionary::Model::FLike>(
                Self->ParentKey,
                Gs2::Dictionary::Domain::Model::FLikeDomain::CreateCacheKey(
                    Self->EntryModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLikeAccessTokenDomain::FModelTask>> FLikeAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLikeAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FLikeAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Dictionary::Model::FLikePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Dictionary::Model::FLike::TypeName,
            ParentKey,
            Gs2::Dictionary::Domain::Model::FLikeDomain::CreateCacheKey(
                EntryModelName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Dictionary::Model::FLike>(obj));
            }
        );
    }

    void FLikeAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Dictionary::Model::FLike::TypeName,
            ParentKey,
            Gs2::Dictionary::Domain::Model::FLikeDomain::CreateCacheKey(
                EntryModelName
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

