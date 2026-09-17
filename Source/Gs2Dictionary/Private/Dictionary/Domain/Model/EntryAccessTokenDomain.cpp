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

#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/Entry.h"
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
#include "Dictionary/Model/Cache/Entry.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Dictionary::Domain::Model
{

    FEntryAccessTokenDomain::FEntryAccessTokenDomain(
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
        ParentKey(Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        ))
    {
    }

    FEntryAccessTokenDomain::FEntryAccessTokenDomain(
        const FEntryAccessTokenDomain& From
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

    FEntryAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FEntryAccessTokenDomain>& Self,
        const Request::FGetEntryRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEntryAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntry>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithEntryModelName(Self->EntryModelName);
        const auto Future = Self->Client->GetEntry(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
        {
            Gs2::Dictionary::Model::Cache::FEntryCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                Request->GetEntryModelName(),
                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                ResultModel->GetItem()
            );
        }
        *Result = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FGetTask>> FEntryAccessTokenDomain::Get(
        Request::FGetEntryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FEntryAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FEntryAccessTokenDomain>& Self,
        const Request::FGetEntryWithSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEntryAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryAccessTokenDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithEntryModelName(Self->EntryModelName);
        const auto Future = Self->Client->GetEntryWithSignature(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Dictionary::Model::Cache::FEntryCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(),
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Request->GetEntryModelName(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    ResultModel->GetItem()
                );
            }
            Domain->Body = ResultModel->GetBody();
            Domain->Signature = ResultModel->GetSignature();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FGetWithSignatureTask>> FEntryAccessTokenDomain::GetWithSignature(
        Request::FGetEntryWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FEntryAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FEntryAccessTokenDomain>& Self,
        const Request::FVerifyEntryRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEntryAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithEntryModelName(Self->EntryModelName);
        const auto Future = Self->Client->VerifyEntry(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FVerifyTask>> FEntryAccessTokenDomain::Verify(
        Request::FVerifyEntryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FEntryAccessTokenDomain::CreateCacheParentKey(
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

    FString FEntryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> EntryModelName
    )
    {
        return FString("") +
            (EntryModelName.IsSet() ? *EntryModelName : "null");
    }

    FEntryAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FEntryAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FEntryAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntry>> Result
    )
    {
        const auto Gs2Snapshot = Self->Gs2;
        const auto ServiceSnapshot = Self->Service;
        const auto NamespaceName = Self->NamespaceName;
        const auto UserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto EntryModelName = Self->EntryModelName;
        const auto TimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto AccessTokenSnapshot = Self->AccessToken;
        Gs2::Dictionary::Model::FEntryPtr Value;
        if (Gs2::Dictionary::Model::Cache::FEntryCache::TryGet(Gs2Snapshot->Cache, NamespaceName, UserId, EntryModelName, TimeOffset, &Value))
        {
            *Result = Value;
            return nullptr;
        }
        const auto Error = Gs2::Dictionary::Model::Cache::FEntryCache::Fetch(
            Gs2Snapshot->Cache, NamespaceName, UserId, EntryModelName, TimeOffset,
            [FetchDomain = MakeShared<FEntryAccessTokenDomain>(Gs2Snapshot, ServiceSnapshot, NamespaceName, AccessTokenSnapshot, EntryModelName)](Gs2::Dictionary::Model::FEntryPtr* OutValue) -> Gs2::Core::Model::FGs2ErrorPtr
            {
                const auto Future = FetchDomain->Get(MakeShared<Gs2::Dictionary::Request::FGetEntryRequest>());
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    return Future->GetTask().Error();
                }
                *OutValue = Future->GetTask().Result();
                Future->EnsureCompletion();
                return nullptr;
            }, &Value
        );
        *Result = Value;
        return Error;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FModelTask>> FEntryAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEntryAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FEntryAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FEntryAccessTokenDomain> Self,
        const TFunction<void(Gs2::Dictionary::Model::FEntryPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FEntryAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FSubscribeWithInitialCallTask>> FEntryAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Dictionary::Model::FEntryPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FEntryAccessTokenDomain::Invalidate()
    {
        Gs2::Dictionary::Model::Cache::FEntryCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            EntryModelName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FEntryAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Dictionary::Model::FEntryPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Dictionary::Domain::FGs2DictionaryDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = AccessToken.IsValid() ? UserId() : TOptional<FString>();
        const TOptional<FString> QueryEntryModelName = EntryModelName;
        const TOptional<int32> QueryTimeOffset = AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto SourceToken = AccessToken;
        Gs2::Auth::Model::FAccessTokenPtr QueryAccessToken;
        if (SourceToken.IsValid()) { QueryAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken); }
        const auto OwnerParentKey = Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheParentKey(QueryNamespaceName, QueryUserId, QueryTimeOffset);

        return Gs2->Cache->Subscribe(
            Gs2::Dictionary::Model::FEntry::TypeName,
            OwnerParentKey,
            Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheKey(QueryEntryModelName),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Dictionary::Model::FEntry>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QueryUserId, QueryEntryModelName, QueryTimeOffset, QueryAccessToken]()
            {
                const auto Owner = WeakGs2.Pin();
                const auto ServiceOwner = WeakService.Pin();
                if (!Owner.IsValid() || !QueryAccessToken.IsValid() || !QueryUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*QueryAccessToken);
                if (TokenSnapshot->GetUserId() != QueryUserId || TokenSnapshot->GetTimeOffset() != QueryTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FEntryAccessTokenDomain>(
                    Owner,
                    ServiceOwner,
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryEntryModelName
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FEntryAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Dictionary::Model::FEntry::TypeName,
            Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? UserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Gs2::Dictionary::Model::Cache::FEntryCache::CreateCacheKey(EntryModelName),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

