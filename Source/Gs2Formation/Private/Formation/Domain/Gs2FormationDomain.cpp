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

// ReSharper disable CppUnusedIncludeDirective

#include "Formation/Domain/Gs2Formation.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"
#include "Formation/Model/Cache/Mold.h"
#include "Formation/Model/Cache/MoldModel.h"
#include "Formation/Model/Cache/Form.h"
#include "Formation/Model/Cache/FormModel.h"
#include "Formation/Model/Cache/PropertyForm.h"

#include "Formation/Model/Cache/Namespace.h"
#include "Formation/Model/Cache/PropertyFormModelMaster.h"
#include "Formation/Model/Cache/FormModelMaster.h"
#include "Formation/Model/Cache/MoldModelMaster.h"
#include "Formation/Model/Cache/CurrentFormMaster.h"
#include "Formation/Model/Cache/MoldModel.h"
#include "Formation/Model/Cache/FormModel.h"
#include "Formation/Model/Cache/PropertyFormModel.h"
#include "Formation/Model/Cache/Mold.h"
#include "Formation/Model/Cache/PropertyForm.h"
#include "Formation/Model/Cache/Form.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Formation::Domain
{

    FGs2FormationDomain::FGs2FormationDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        ParentKey("formation")
    {
    }

    FGs2FormationDomain::FGs2FormationDomain(
        const FGs2FormationDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2FormationDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Formation::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Formation::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCreateNamespaceTask>> FGs2FormationDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
    )
    {
        const auto Future = Self->Client->DumpUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FDumpUserDataTask>> FGs2FormationDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckDumpUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCheckDumpUserDataTask>> FGs2FormationDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
    )
    {
        const auto Future = Self->Client->CleanUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCleanUserDataTask>> FGs2FormationDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckCleanUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCheckCleanUserDataTask>> FGs2FormationDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
    )
    {
        const auto Future = Self->Client->PrepareImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUploadToken().IsSet())
            {
                Self->UploadToken = Domain->UploadToken = ResultModel->GetUploadToken();
            }
            if (ResultModel->GetUploadUrl().IsSet())
            {
                Self->UploadUrl = Domain->UploadUrl = ResultModel->GetUploadUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FPrepareImportUserDataTask>> FGs2FormationDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
    )
    {
        const auto Future = Self->Client->ImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FImportUserDataTask>> FGs2FormationDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2FormationDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCheckImportUserDataTask>> FGs2FormationDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Formation::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2FormationDomain::Namespaces(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FGs2FormationDomain::SubscribeNamespaces(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FNamespace::TypeName,
            Gs2::Formation::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2FormationDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FNamespace::TypeName,
            Gs2::Formation::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2FormationDomain::FCollectNamespacesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Formation::Model::FNamespacePtr>>, public TSharedFromThis<FCollectNamespacesTask>
    {
        const TSharedPtr<FGs2FormationDomain> Self;
        const TFunction<void(TArray<Gs2::Formation::Model::FNamespacePtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectNamespacesTask(const TSharedPtr<FGs2FormationDomain>& Self, TFunction<void(TArray<Gs2::Formation::Model::FNamespacePtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectNamespacesTask(const FCollectNamespacesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Formation::Model::FNamespacePtr>>> Result) override
        {
            TArray<Gs2::Formation::Model::FNamespacePtr> Items;
            auto Iterator = Self->Namespaces(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Formation::Model::FNamespacePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2FormationDomain::SubscribeNamespaces(
        TFunction<void(TArray<Gs2::Formation::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Formation::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Formation::Model::FNamespace::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Formation::Model::FNamespacePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Formation::Model::FNamespace>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2FormationDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2FormationDomain::InvalidateNamespaces(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Formation::Model::FNamespace::TypeName,
            Gs2::Formation::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2FormationDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2FormationDomain>& Self, TFunction<void(TArray<Gs2::Formation::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FGs2FormationDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FSubscribeNamespacesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Self, TFunction<void(TArray<Gs2::Formation::Model::FNamespacePtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeNamespaces(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2FormationDomain::FSubscribeNamespacesWithInitialCallTask>> FGs2FormationDomain::SubscribeNamespacesWithInitialCall(TFunction<void(TArray<Gs2::Formation::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain> FGs2FormationDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Formation::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2FormationDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "AddMoldCapacityByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FAddMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAddMoldCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FMoldModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMoldModel()
                );
                    }


        }
        if (Method == "SetMoldCapacityByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FSetMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSetMoldCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FMoldModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMoldModel()
                );
                    }


        }
        if (Method == "AcquireActionsToFormProperties") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToFormPropertiesResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FFormCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    ResultModel->GetItem()->GetIndex().Get(int32{}),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMold()
                );
                    }


        }
        if (Method == "SetFormByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FSetFormByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSetFormByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FFormCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    ResultModel->GetItem()->GetIndex().Get(int32{}),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMold()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FMoldModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMoldModel()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetFormModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FFormModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetFormModel()
                );
                    }




        }
        if (Method == "AcquireActionsToPropertyFormProperties") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToPropertyFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToPropertyFormPropertiesResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FPropertyFormCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetPropertyFormModelName(),
                    ResultModel->GetItem()->GetPropertyId(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2FormationDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "SubMoldCapacityByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FSubMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSubMoldCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FMoldModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMoldModel()
                );
                    }


        }
    }

    void FGs2FormationDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "add_mold_capacity_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FAddMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAddMoldCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FMoldModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMoldModel()
                );
                    }


        }
        if (Method == "set_mold_capacity_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FSetMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSetMoldCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FMoldModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMoldModel()
                );
                    }


        }
        if (Method == "acquire_actions_to_form_properties") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToFormPropertiesResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FFormCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    ResultModel->GetItem()->GetIndex().Get(int32{}),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMold()
                );
                    }


        }
        if (Method == "set_form_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FSetFormByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSetFormByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FFormCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    ResultModel->GetItem()->GetIndex().Get(int32{}),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FMoldCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMold()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FMoldModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetMoldModel()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetFormModel() != nullptr)
                    {


                Gs2::Formation::Model::Cache::FFormModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetMoldModelName(),
                    TimeOffset,
                    ResultModel->GetFormModel()
                );
                    }




        }
        if (Method == "acquire_actions_to_property_form_properties") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToPropertyFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToPropertyFormPropertiesResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Formation::Model::Cache::FPropertyFormCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetPropertyFormModelName(),
                    ResultModel->GetItem()->GetPropertyId(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2FormationDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
