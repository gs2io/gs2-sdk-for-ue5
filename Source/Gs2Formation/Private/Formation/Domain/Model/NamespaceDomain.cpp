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

#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey("formation:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
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
            
        }
        const auto Domain = Self;
        Domain->Status = Domain->Status = ResultModel->GetStatus();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FNamespace>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
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
            
            {
                const auto ParentKey = FString("formation:Namespace");
                const auto Key = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FNamespace::TypeName,
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
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
            
            {
                const auto ParentKey = FString("formation:Namespace");
                const auto Key = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FNamespace::TypeName,
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
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
            
            {
                const auto ParentKey = FString("formation:Namespace");
                const auto Key = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Formation::Model::FNamespace::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateFormModelMasterTask::FCreateFormModelMasterTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FCreateFormModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateFormModelMasterTask::FCreateFormModelMasterTask(
        const FCreateFormModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateFormModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateFormModelMaster(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "FormModelMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FFormModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Formation::Domain::Model::FFormModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateFormModelMasterTask>> FNamespaceDomain::CreateFormModelMaster(
        Request::FCreateFormModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateFormModelMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateMoldModelMasterTask::FCreateMoldModelMasterTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FCreateMoldModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateMoldModelMasterTask::FCreateMoldModelMasterTask(
        const FCreateMoldModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateMoldModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateMoldModelMaster(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModelMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Formation::Domain::Model::FMoldModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateMoldModelMasterTask>> FNamespaceDomain::CreateMoldModelMaster(
        Request::FCreateMoldModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateMoldModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain> FNamespaceDomain::CurrentFormMaster(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FCurrentFormMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
        );
    }

    Gs2::Formation::Domain::Iterator::FDescribeMoldModelsIteratorPtr FNamespaceDomain::MoldModels(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeMoldModelsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelDomain> FNamespaceDomain::MoldModel(
        const FString MoldName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FMoldModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            MoldName
        );
    }

    Gs2::Formation::Domain::Iterator::FDescribeFormModelsIteratorPtr FNamespaceDomain::FormModels(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeFormModelsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FFormModelDomain> FNamespaceDomain::FormModel(
        const FString FormModelName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FFormModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            FormModelName
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FUserAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Formation::Domain::Iterator::FDescribeFormModelMastersIteratorPtr FNamespaceDomain::FormModelMasters(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeFormModelMastersIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain> FNamespaceDomain::FormModelMaster(
        const FString FormModelName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FFormModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            FormModelName
        );
    }

    Gs2::Formation::Domain::Iterator::FDescribeMoldModelMastersIteratorPtr FNamespaceDomain::MoldModelMasters(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeMoldModelMastersIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelMasterDomain> FNamespaceDomain::MoldModelMaster(
        const FString MoldName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FMoldModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            MoldName
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("formation:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FNamespace> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Formation::Model::FNamespace>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FNamespace::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "namespace")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Formation::Model::FNamespace>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

