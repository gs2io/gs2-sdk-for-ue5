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

#include "Dictionary/Domain/Model/EntryModel.h"
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

    FEntryModelDomain::FEntryModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> EntryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Dictionary::FGs2DictionaryRestClient>(Session)),
        NamespaceName(NamespaceName),
        EntryName(EntryName),
        ParentKey(Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "EntryModel"
        ))
    {
    }

    FEntryModelDomain::FEntryModelDomain(
        const FEntryModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        EntryName(From.EntryName),
        ParentKey(From.ParentKey)
    {

    }

    FEntryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FEntryModelDomain> Self,
        const Request::FGetEntryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEntryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithEntryName(Self->EntryName);
        const auto Future = Self->Client->GetEntryModel(
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
                const auto ParentKey = Gs2::Dictionary::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "EntryModel"
                );
                const auto Key = Gs2::Dictionary::Domain::Model::FEntryModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FEntryModel::TypeName,
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

    TSharedPtr<FAsyncTask<FEntryModelDomain::FGetTask>> FEntryModelDomain::Get(
        Request::FGetEntryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FEntryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> EntryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (EntryName.IsSet() ? *EntryName : "null") + ":" +
            ChildType;
    }

    FString FEntryModelDomain::CreateCacheKey(
        TOptional<FString> EntryName
    )
    {
        return FString("") +
            (EntryName.IsSet() ? *EntryName : "null");
    }

    FEntryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FEntryModelDomain> Self
    ): Self(Self)
    {

    }

    FEntryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEntryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Dictionary::Model::FEntryModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Dictionary::Model::FEntryModel>(
            Self->ParentKey,
            Gs2::Dictionary::Domain::Model::FEntryModelDomain::CreateCacheKey(
                Self->EntryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Dictionary::Request::FGetEntryModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Dictionary::Domain::Model::FEntryModelDomain::CreateCacheKey(
                    Self->EntryName
                );
                Self->Cache->Put(
                    Gs2::Dictionary::Model::FEntryModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "entryModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Dictionary::Model::FEntryModel>(
                Self->ParentKey,
                Gs2::Dictionary::Domain::Model::FEntryModelDomain::CreateCacheKey(
                    Self->EntryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEntryModelDomain::FModelTask>> FEntryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEntryModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEntryModelDomain::Subscribe(
        TFunction<void(Gs2::Dictionary::Model::FEntryModelPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Dictionary::Model::FEntryModel::TypeName,
            ParentKey,
            Gs2::Dictionary::Domain::Model::FEntryModelDomain::CreateCacheKey(
                EntryName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Dictionary::Model::FEntryModel>(obj));
            }
        );
    }

    void FEntryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Dictionary::Model::FEntryModel::TypeName,
            ParentKey,
            Gs2::Dictionary::Domain::Model::FEntryModelDomain::CreateCacheKey(
                EntryName
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

