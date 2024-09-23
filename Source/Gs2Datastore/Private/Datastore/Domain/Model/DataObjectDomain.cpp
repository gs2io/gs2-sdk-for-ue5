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

#include "Datastore/Domain/Model/DataObject.h"
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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Datastore::Domain::Model
{

    FDataObjectDomain::FDataObjectDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Datastore::Domain::FGs2DatastoreDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> DataObjectName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        DataObjectName(DataObjectName),
        ParentKey(Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "DataObject"
        ))
    {
    }

    FDataObjectDomain::FDataObjectDomain(
        const FDataObjectDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        DataObjectName(From.DataObjectName),
        ParentKey(From.ParentKey)
    {

    }

    FDataObjectDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FUpdateDataObjectByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDataObjectName(Self->DataObjectName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateDataObjectByUserId(
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
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FUpdateTask>> FDataObjectDomain::Update(
        Request::FUpdateDataObjectByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FPrepareReUploadTask::FPrepareReUploadTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FPrepareReUploadByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareReUploadTask::FPrepareReUploadTask(
        const FPrepareReUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareReUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDataObjectName(Self->DataObjectName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PrepareReUploadByUserId(
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
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->UploadUrl = *ResultModel->GetUploadUrl();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareReUploadTask>> FDataObjectDomain::PrepareReUpload(
        Request::FPrepareReUploadByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareReUploadTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FDoneUploadTask::FDoneUploadTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FDoneUploadByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FDoneUploadTask::FDoneUploadTask(
        const FDoneUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FDoneUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDataObjectName(Self->DataObjectName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DoneUploadByUserId(
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
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
                Self->Gs2->Cache->ClearListCache(
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
                    Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->DataObjectName,
                        "DataObjectHistory"
                    )
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FDoneUploadTask>> FDataObjectDomain::DoneUpload(
        Request::FDoneUploadByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDoneUploadTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FDeleteDataObjectByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->DeleteDataObjectByUserId(
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
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FDeleteTask>> FDataObjectDomain::Delete(
        Request::FDeleteDataObjectByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::FPrepareDownloadByUserIdAndDataObjectNameTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::FPrepareDownloadByUserIdAndDataObjectNameTask(
        const FPrepareDownloadByUserIdAndDataObjectNameTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareDownloadByUserIdAndDataObjectName(
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
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->FileUrl = *ResultModel->GetFileUrl();
            Domain->ContentLength = *ResultModel->GetContentLength();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask>> FDataObjectDomain::PrepareDownloadByUserIdAndDataObjectName(
        Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask(
        const FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
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
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->FileUrl = *ResultModel->GetFileUrl();
            Domain->ContentLength = *ResultModel->GetContentLength();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>> FDataObjectDomain::PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
        Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>>(this->AsShared(), Request);
    }

    Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIteratorPtr FDataObjectDomain::DataObjectHistories(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            DataObjectName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FDataObjectDomain::SubscribeDataObjectHistories(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                DataObjectName,
                "DataObjectHistory"
            ),
            Callback
        );
    }

    void FDataObjectDomain::UnsubscribeDataObjectHistories(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                DataObjectName,
                "DataObjectHistory"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain> FDataObjectDomain::DataObjectHistory(
        const FString Generation
    )
    {
        return MakeShared<Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            DataObjectName,
            Generation == TEXT("") ? TOptional<FString>() : TOptional<FString>(Generation)
        );
    }

    FString FDataObjectDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> DataObjectName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (DataObjectName.IsSet() ? *DataObjectName : "null") + ":" +
            ChildType;
    }

    FString FDataObjectDomain::CreateCacheKey(
        TOptional<FString> DataObjectName
    )
    {
        return FString("") +
            (DataObjectName.IsSet() ? *DataObjectName : "null");
    }

    FDataObjectDomain::FModelTask::FModelTask(
        const TSharedPtr<FDataObjectDomain> Self
    ): Self(Self)
    {

    }

    FDataObjectDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObject>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Datastore::Model::FDataObject> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Datastore::Model::FDataObject>(
            Self->ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                Self->DataObjectName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FModelTask>> FDataObjectDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataObjectDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDataObjectDomain::Subscribe(
        TFunction<void(Gs2::Datastore::Model::FDataObjectPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Datastore::Model::FDataObject::TypeName,
            ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                DataObjectName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Datastore::Model::FDataObject>(obj));
            }
        );
    }

    void FDataObjectDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Datastore::Model::FDataObject::TypeName,
            ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                DataObjectName
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

