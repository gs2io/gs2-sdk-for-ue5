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

#include "Formation/Domain/Model/FormModelMaster.h"
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

    FFormModelMasterDomain::FFormModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> FormModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        FormModelName(FormModelName),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "FormModelMaster"
        ))
    {
    }

    FFormModelMasterDomain::FFormModelMasterDomain(
        const FFormModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FFormModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FFormModelMasterDomain> Self,
        const Request::FGetFormModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FFormModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithFormModelName(Self->FormModelName);
        const auto Future = Self->Client->GetFormModelMaster(
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormModelMasterDomain::FGetTask>> FFormModelMasterDomain::Get(
        Request::FGetFormModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFormModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FFormModelMasterDomain> Self,
        const Request::FUpdateFormModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithFormModelName(Self->FormModelName);
        const auto Future = Self->Client->UpdateFormModelMaster(
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormModelMasterDomain::FUpdateTask>> FFormModelMasterDomain::Update(
        Request::FUpdateFormModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FFormModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFormModelMasterDomain> Self,
        const Request::FDeleteFormModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithFormModelName(Self->FormModelName);
        const auto Future = Self->Client->DeleteFormModelMaster(
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
                Self->Cache->Delete(Gs2::Formation::Model::FFormModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormModelMasterDomain::FDeleteTask>> FFormModelMasterDomain::Delete(
        Request::FDeleteFormModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFormModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> FormModelName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (FormModelName.IsSet() ? *FormModelName : "null") + ":" +
            ChildType;
    }

    FString FFormModelMasterDomain::CreateCacheKey(
        TOptional<FString> FormModelName
    )
    {
        return FString() +
            (FormModelName.IsSet() ? *FormModelName : "null");
    }

    FFormModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FFormModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FFormModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFormModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FFormModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FFormModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Formation::Model::FFormModelMaster>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FFormModelMasterDomain::CreateCacheKey(
                Self->FormModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetFormModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FFormModelMasterDomain::CreateCacheKey(
                    Self->FormModelName
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FFormModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "formModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Formation::Model::FFormModelMaster>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FFormModelMasterDomain::CreateCacheKey(
                    Self->FormModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormModelMasterDomain::FModelTask>> FFormModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFormModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

