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

#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Domain/Model/EntryModelMaster.h"
#include "Dictionary/Domain/Model/Entry.h"
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Domain/Model/CurrentEntryMaster.h"
#include "Dictionary/Domain/Model/User.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Dictionary::Domain::Model
{

    FEntryAccessTokenDomain::FEntryAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> EntryModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        EntryModelName(EntryModelName),
        ParentKey(Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Entry"
        ))
    {
    }

    FEntryAccessTokenDomain::FEntryAccessTokenDomain(
        const FEntryAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FEntryAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FEntryAccessTokenDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Entry"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FEntry::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FGetTask>> FEntryAccessTokenDomain::Get(
        Request::FGetEntryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FEntryAccessTokenDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FEntryAccessTokenDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Entry"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FEntry::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        Domain->Body = *ResultModel->GetBody();
        Domain->Signature = *ResultModel->GetSignature();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FGetWithSignatureTask>> FEntryAccessTokenDomain::GetWithSignature(
        Request::FGetEntryWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FString FEntryAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> EntryModelName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (EntryModelName.IsSet() ? *EntryModelName : "null") + ":" +
            ChildType;
    }

    FString FEntryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> EntryModelName
    )
    {
        return FString() +
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Dictionary::Model::FEntry> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Dictionary::Model::FEntry>(
            Self->ParentKey,
            Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                Self->EntryModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Dictionary::Request::FGetEntryRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                    Self->EntryModelName
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FEntry::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "entry")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Dictionary::Model::FEntry>(
                Self->ParentKey,
                Gs2::Dictionary::Domain::Model::FEntryDomain::CreateCacheKey(
                    Self->EntryModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryAccessTokenDomain::FModelTask>> FEntryAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEntryAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

