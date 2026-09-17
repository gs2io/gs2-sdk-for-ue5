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

#include "Inventory/Domain/Gs2Inventory.h"
#include "Inventory/Domain/Model/Namespace.h"
#include "Inventory/Domain/Model/InventoryModelMaster.h"
#include "Inventory/Domain/Model/InventoryModel.h"
#include "Inventory/Domain/Model/ItemModelMaster.h"
#include "Inventory/Domain/Model/ItemModel.h"
#include "Inventory/Domain/Model/SimpleInventoryModelMaster.h"
#include "Inventory/Domain/Model/SimpleInventoryModel.h"
#include "Inventory/Domain/Model/SimpleItemModelMaster.h"
#include "Inventory/Domain/Model/SimpleItemModel.h"
#include "Inventory/Domain/Model/BigInventoryModelMaster.h"
#include "Inventory/Domain/Model/BigInventoryModel.h"
#include "Inventory/Domain/Model/BigItemModelMaster.h"
#include "Inventory/Domain/Model/BigItemModel.h"
#include "Inventory/Domain/Model/CurrentItemModelMaster.h"
#include "Inventory/Domain/Model/Inventory.h"
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/SimpleInventory.h"
#include "Inventory/Domain/Model/SimpleItem.h"
#include "Inventory/Domain/Model/BigInventory.h"
#include "Inventory/Domain/Model/BigItem.h"
#include "Inventory/Domain/Model/User.h"
#include "Inventory/Domain/Model/UserAccessToken.h"
#include "Inventory/Model/Cache/Inventory.h"
#include "Inventory/Model/Cache/ItemSet.h"
#include "Inventory/Model/Cache/ItemModel.h"
#include "Grade/Model/Cache/Status.h"
#include "Inventory/Model/Cache/ReferenceOf.h"
#include "Inventory/Model/Cache/SimpleItem.h"
#include "Inventory/Model/Cache/SimpleInventory.h"
#include "Inventory/Model/Cache/BigItem.h"

#include "Inventory/Model/Cache/Namespace.h"
#include "Inventory/Model/Cache/SimpleInventoryModelMaster.h"
#include "Inventory/Model/Cache/BigInventoryModelMaster.h"
#include "Inventory/Model/Cache/InventoryModelMaster.h"
#include "Inventory/Model/Cache/CurrentItemModelMaster.h"
#include "Inventory/Model/Cache/InventoryModel.h"
#include "Inventory/Model/Cache/ItemModel.h"
#include "Inventory/Model/Cache/Inventory.h"
#include "Inventory/Model/Cache/ItemSet.h"
#include "Grade/Model/Cache/Status.h"
#include "Inventory/Model/Cache/ReferenceOf.h"
#include "Inventory/Model/Cache/SimpleItem.h"
#include "Inventory/Model/Cache/SimpleInventory.h"
#include "Inventory/Model/Cache/SimpleItemModel.h"
#include "Inventory/Model/Cache/BigItem.h"
#include "Inventory/Model/Cache/BigInventory.h"
#include "Inventory/Model/Cache/BigItemModel.h"
#include "Inventory/Model/Cache/SimpleItemModelMaster.h"
#include "Inventory/Model/Cache/SimpleInventoryModel.h"
#include "Inventory/Model/Cache/BigInventoryModel.h"
#include "Inventory/Model/Cache/BigItemModelMaster.h"
#include "Inventory/Model/Cache/ItemModelMaster.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Inventory::Domain
{

    FGs2InventoryDomain::FGs2InventoryDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        ParentKey("inventory")
    {
    }

    FGs2InventoryDomain::FGs2InventoryDomain(
        const FGs2InventoryDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2InventoryDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FNamespaceDomain>> Result
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


        Gs2::Inventory::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FCreateNamespaceTask>> FGs2InventoryDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2InventoryDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2InventoryDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FDumpUserDataTask>> FGs2InventoryDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2InventoryDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2InventoryDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FCheckDumpUserDataTask>> FGs2InventoryDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2InventoryDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2InventoryDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FCleanUserDataTask>> FGs2InventoryDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2InventoryDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2InventoryDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FCheckCleanUserDataTask>> FGs2InventoryDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2InventoryDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2InventoryDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FPrepareImportUserDataTask>> FGs2InventoryDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2InventoryDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2InventoryDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FImportUserDataTask>> FGs2InventoryDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2InventoryDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2InventoryDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2InventoryDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FCheckImportUserDataTask>> FGs2InventoryDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2InventoryDomain::Namespaces(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FGs2InventoryDomain::SubscribeNamespaces(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FNamespace::TypeName,
            Gs2::Inventory::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2InventoryDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FNamespace::TypeName,
            Gs2::Inventory::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2InventoryDomain::FCollectNamespacesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inventory::Model::FNamespacePtr>>, public TSharedFromThis<FCollectNamespacesTask>
    {
        const TSharedPtr<FGs2InventoryDomain> Self;
        const TFunction<void(TArray<Gs2::Inventory::Model::FNamespacePtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectNamespacesTask(const TSharedPtr<FGs2InventoryDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FNamespacePtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectNamespacesTask(const FCollectNamespacesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FNamespacePtr>>> Result) override
        {
            TArray<Gs2::Inventory::Model::FNamespacePtr> Items;
            auto Iterator = Self->Namespaces(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Inventory::Model::FNamespacePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2InventoryDomain::SubscribeNamespaces(
        TFunction<void(TArray<Gs2::Inventory::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Inventory::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Inventory::Model::FNamespace::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Inventory::Model::FNamespacePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Inventory::Model::FNamespace>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2InventoryDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2InventoryDomain::InvalidateNamespaces(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Inventory::Model::FNamespace::TypeName,
            Gs2::Inventory::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2InventoryDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2InventoryDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FGs2InventoryDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FSubscribeNamespacesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Self, TFunction<void(TArray<Gs2::Inventory::Model::FNamespacePtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeNamespaces(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FSubscribeNamespacesWithInitialCallTask>> FGs2InventoryDomain::SubscribeNamespacesWithInitialCall(TFunction<void(TArray<Gs2::Inventory::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FNamespaceDomain> FGs2InventoryDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2InventoryDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "AddCapacityByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAddCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "SetCapacityByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FSetCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "AcquireItemSetByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireItemSetByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireItemSetByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItemModel() != nullptr)
                    {


                Gs2::Inventory::Model::Cache::FItemModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItemModel()
                );
                    }
                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(), Item->GetName(),
                            TimeOffset, Item
                        );
                    }
                    Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                        Gs2->Cache,
                        RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), RequestModel->GetItemName(),
                        TimeOffset, ResultModel->GetItems()
                    );
                }
                Gs2->Cache->SetListCached(
                    Gs2::Inventory::Model::FItemSet::TypeName,
                    Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        TimeOffset
                    )
                );

            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    TimeOffset
                );
                const auto Key = Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                    ParentKey,
                    Key,
                    &Item
                );
                if (Item == nullptr || *Item->GetRevision() < *ResultModel->GetInventory()->GetRevision())
                {
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item2 : *ResultModel->GetItems())
                    {
                        if (Item2->GetExpiresAt().IsSet())
                        {
                            if (*Item2->GetExpiresAt() != 0 && ExpiresAt > *Item2->GetExpiresAt())
                            {
                                ExpiresAt = *Item2->GetExpiresAt();
                            }
                        }
                    }
                    Gs2->Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        if (Method == "AcquireItemSetWithGradeByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireItemSetWithGradeByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    ResultModel->GetItem()->GetName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetStatus() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Grade::Model::Cache::FStatusCache::Put(
                    Gs2->Cache,

                    Gs2::Grade::Model::FStatus::GetNamespaceNameFromGrn(ResultModel->GetStatus()->GetStatusId().Get(FString())),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetStatus()->GetGradeName(),
                    ResultModel->GetStatus()->GetPropertyId(),
                    TimeOffset,
                    ResultModel->GetStatus()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetItemModel() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FItemModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    ResultModel->GetItem()->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItemModel()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetInventory() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetInventory()
                );
                    }




        }
        if (Method == "AddReferenceOfByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAddReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddReferenceOfByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItemSet() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    RequestModel->GetItemSetName(),
                    TimeOffset,
                    ResultModel->GetItemSet()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetItemModel() != nullptr)
                    {


                Gs2::Inventory::Model::Cache::FItemModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItemModel()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetInventory() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetInventory()
                );
                    }



        }
        if (Method == "DeleteReferenceOfByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FDeleteReferenceOfByUserIdResult::FromJson(ResultModelJson);

                      if (!(RequestModel->GetUserId()).IsSet())
                          {
                            return;
                            }
                      Gs2::Inventory::Model::Cache::FItemSetCache::Delete(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    RequestModel->GetItemSetName(),
                    TimeOffset
                );

                      Gs2::Inventory::Model::Cache::FItemModelCache::Delete(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    TimeOffset
                );
                      if (!(RequestModel->GetUserId()).IsSet())
                          {
                            return;
                            }
                      Gs2::Inventory::Model::Cache::FInventoryCache::Delete(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    TimeOffset
                );



        }
        if (Method == "AcquireSimpleItemsByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireSimpleItemsByUserIdResult::FromJson(ResultModelJson);

                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FSimpleItemCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(),
                            TimeOffset, Item
                        );
                    }
                }
        }
        if (Method == "SetSimpleItemsByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetSimpleItemsByUserIdResult::FromJson(ResultModelJson);

                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FSimpleItemCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(),
                            TimeOffset, Item
                        );
                    }
                }
        }
        if (Method == "AcquireBigItemByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireBigItemByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FBigItemCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "SetBigItemByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FSetBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetBigItemByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FBigItemCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2InventoryDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "ConsumeItemSetByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FConsumeItemSetByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FConsumeItemSetByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItemModel() != nullptr)
                    {


                Gs2::Inventory::Model::Cache::FItemModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItemModel()
                );
                    }
                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(), Item->GetName(),
                            TimeOffset, Item
                        );
                    }
                    Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                        Gs2->Cache,
                        RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), RequestModel->GetItemName(),
                        TimeOffset, ResultModel->GetItems()
                    );
                }
                Gs2->Cache->SetListCached(
                    Gs2::Inventory::Model::FItemSet::TypeName,
                    Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        TimeOffset
                    )
                );

            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    TimeOffset
                );
                const auto Key = Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                    ParentKey,
                    Key,
                    &Item
                );
                if (Item == nullptr || *Item->GetRevision() < *ResultModel->GetInventory()->GetRevision())
                {
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item2 : *ResultModel->GetItems())
                    {
                        if (Item2->GetExpiresAt().IsSet())
                        {
                            if (*Item2->GetExpiresAt() != 0 && ExpiresAt > *Item2->GetExpiresAt())
                            {
                                ExpiresAt = *Item2->GetExpiresAt();
                            }
                        }
                    }
                    Gs2->Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        if (Method == "ConsumeSimpleItemsByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FConsumeSimpleItemsByUserIdResult::FromJson(ResultModelJson);

                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FSimpleItemCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(),
                            TimeOffset, Item
                        );
                    }
                }
        }
        if (Method == "ConsumeBigItemByUserId") {
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
            const auto RequestModel = Gs2::Inventory::Request::FConsumeBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FConsumeBigItemByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FBigItemCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2InventoryDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "add_capacity_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAddCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "set_capacity_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FSetCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetCapacityByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "acquire_item_set_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireItemSetByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireItemSetByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItemModel() != nullptr)
                    {


                Gs2::Inventory::Model::Cache::FItemModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItemModel()
                );
                    }
                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(), Item->GetName(),
                            TimeOffset, Item
                        );
                    }
                    Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                        Gs2->Cache,
                        RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), RequestModel->GetItemName(),
                        TimeOffset, ResultModel->GetItems()
                    );
                }
                Gs2->Cache->SetListCached(
                    Gs2::Inventory::Model::FItemSet::TypeName,
                    Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        TimeOffset
                    )
                );

            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    TimeOffset
                );
                const auto Key = Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                    ParentKey,
                    Key,
                    &Item
                );
                if (Item == nullptr || *Item->GetRevision() < *ResultModel->GetInventory()->GetRevision())
                {
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item2 : *ResultModel->GetItems())
                    {
                        if (Item2->GetExpiresAt().IsSet())
                        {
                            if (*Item2->GetExpiresAt() != 0 && ExpiresAt > *Item2->GetExpiresAt())
                            {
                                ExpiresAt = *Item2->GetExpiresAt();
                            }
                        }
                    }
                    Gs2->Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        if (Method == "acquire_item_set_with_grade_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireItemSetWithGradeByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    ResultModel->GetItem()->GetName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetStatus() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Grade::Model::Cache::FStatusCache::Put(
                    Gs2->Cache,

                    Gs2::Grade::Model::FStatus::GetNamespaceNameFromGrn(ResultModel->GetStatus()->GetStatusId().Get(FString())),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetStatus()->GetGradeName(),
                    ResultModel->GetStatus()->GetPropertyId(),
                    TimeOffset,
                    ResultModel->GetStatus()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetItemModel() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FItemModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    ResultModel->GetItem()->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItemModel()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetInventory() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    ResultModel->GetItem()->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetInventory()
                );
                    }




        }
        if (Method == "add_reference_of_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAddReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddReferenceOfByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItemSet() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    RequestModel->GetItemSetName(),
                    TimeOffset,
                    ResultModel->GetItemSet()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetItemModel() != nullptr)
                    {


                Gs2::Inventory::Model::Cache::FItemModelCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItemModel()
                );
                    }
                    if (ResultModel.IsValid() && ResultModel->GetInventory() != nullptr)
                    {

                if (!(RequestModel->GetUserId()).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FInventoryCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    TimeOffset,
                    ResultModel->GetInventory()
                );
                    }



        }
        if (Method == "delete_reference_of_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FDeleteReferenceOfByUserIdResult::FromJson(ResultModelJson);

                      if (!(RequestModel->GetUserId()).IsSet())
                          {
                            return;
                            }
                      Gs2::Inventory::Model::Cache::FItemSetCache::Delete(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    RequestModel->GetItemSetName(),
                    TimeOffset
                );

                      Gs2::Inventory::Model::Cache::FItemModelCache::Delete(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    RequestModel->GetItemName(),
                    TimeOffset
                );
                      if (!(RequestModel->GetUserId()).IsSet())
                          {
                            return;
                            }
                      Gs2::Inventory::Model::Cache::FInventoryCache::Delete(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    TimeOffset
                );



        }
        if (Method == "acquire_simple_items_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireSimpleItemsByUserIdResult::FromJson(ResultModelJson);

                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FSimpleItemCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(),
                            TimeOffset, Item
                        );
                    }
                }
        }
        if (Method == "set_simple_items_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetSimpleItemsByUserIdResult::FromJson(ResultModelJson);

                if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
                {
                    for (const auto& Item : *ResultModel->GetItems())
                    {
                        if (!Item.IsValid()) continue;
                        Gs2::Inventory::Model::Cache::FSimpleItemCache::Put(
                            Gs2->Cache,
                            RequestModel->GetNamespaceName(), RequestModel->GetUserId(), RequestModel->GetInventoryName(), Item->GetItemName(),
                            TimeOffset, Item
                        );
                    }
                }
        }
        if (Method == "acquire_big_item_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FAcquireBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireBigItemByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FBigItemCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "set_big_item_by_user_id") {
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
            const auto RequestModel = Gs2::Inventory::Request::FSetBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetBigItemByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Inventory::Model::Cache::FBigItemCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    RequestModel->GetInventoryName(),
                    ResultModel->GetItem()->GetItemName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2InventoryDomain::HandleNotification(
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
