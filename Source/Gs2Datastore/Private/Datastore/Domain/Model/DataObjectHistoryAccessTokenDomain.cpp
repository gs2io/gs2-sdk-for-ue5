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

#include "Datastore/Domain/Model/DataObjectHistoryAccessToken.h"
#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/Namespace.h"
#include "Datastore/Domain/Model/DataObject.h"
#include "Datastore/Domain/Model/DataObjectAccessToken.h"
#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/DataObjectHistoryAccessToken.h"
#include "Datastore/Domain/Model/User.h"
#include "Datastore/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Datastore::Domain::Model
{

    FDataObjectHistoryAccessTokenDomain::FDataObjectHistoryAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Datastore::Domain::FGs2DatastoreDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> DataObjectName,
        const TOptional<FString> Generation
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        DataObjectName(DataObjectName),
        Generation(Generation),
        ParentKey(Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            DataObjectName,
            "DataObjectHistory"
        ))
    {
    }

    FDataObjectHistoryAccessTokenDomain::FDataObjectHistoryAccessTokenDomain(
        const FDataObjectHistoryAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        DataObjectName(From.DataObjectName),
        Generation(From.Generation),
        ParentKey(From.ParentKey)
    {

    }

    FDataObjectHistoryAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FDataObjectHistoryAccessTokenDomain>& Self,
        const Request::FGetDataObjectHistoryRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectHistoryAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectHistoryAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithDataObjectName(Self->DataObjectName)
            ->WithGeneration(Self->Generation);
        const auto Future = Self->Client->GetDataObjectHistory(
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
                const auto ParentKey = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->DataObjectName,
                    "DataObjectHistory"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGeneration()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
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

    TSharedPtr<FAsyncTask<FDataObjectHistoryAccessTokenDomain::FGetTask>> FDataObjectHistoryAccessTokenDomain::Get(
        Request::FGetDataObjectHistoryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FDataObjectHistoryAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> DataObjectName,
        TOptional<FString> Generation,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (DataObjectName.IsSet() ? *DataObjectName : "null") + ":" +
            (Generation.IsSet() ? *Generation : "null") + ":" +
            ChildType;
    }

    FString FDataObjectHistoryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> Generation
    )
    {
        return FString("") +
            (Generation.IsSet() ? *Generation : "null");
    }

    FDataObjectHistoryAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FDataObjectHistoryAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FDataObjectHistoryAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectHistoryAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Datastore::Model::FDataObjectHistory>(
            Self->ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                Self->Generation
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Datastore::Request::FGetDataObjectHistoryRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                    Self->Generation
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "dataObjectHistory")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Datastore::Model::FDataObjectHistory>(
                Self->ParentKey,
                Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                    Self->Generation
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectHistoryAccessTokenDomain::FModelTask>> FDataObjectHistoryAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataObjectHistoryAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDataObjectHistoryAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Datastore::Model::FDataObjectHistoryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                Generation
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>(obj));
            }
        );
    }

    void FDataObjectHistoryAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                Generation
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

