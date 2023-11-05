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

#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FFormDomain::FFormDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> MoldModelName,
        const TOptional<int32> Index
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        MoldModelName(MoldModelName),
        Index(Index),
        ParentKey(Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            MoldModelName,
            "Form"
        ))
    {
    }

    FFormDomain::FFormDomain(
        const FFormDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        MoldModelName(From.MoldModelName),
        Index(From.Index),
        ParentKey(From.ParentKey)
    {

    }

    FFormDomain::FGetTask::FGetTask(
        const TSharedPtr<FFormDomain> Self,
        const Request::FGetFormByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->GetFormByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FFormModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FGetTask>> FFormDomain::Get(
        Request::FGetFormByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFormDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FFormDomain> Self,
        const Request::FGetFormWithSignatureByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->GetFormWithSignatureByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FFormModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->Body = *ResultModel->GetBody();
            Domain->Signature = *ResultModel->GetSignature();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FGetWithSignatureTask>> FFormDomain::GetWithSignature(
        Request::FGetFormWithSignatureByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FFormDomain::FSetTask::FSetTask(
        const TSharedPtr<FFormDomain> Self,
        const Request::FSetFormByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FSetTask::FSetTask(
        const FSetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FSetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->SetFormByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FFormModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetFormModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FSetTask>> FFormDomain::Set(
        Request::FSetFormByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetTask>>(this->AsShared(), Request);
    }

    FFormDomain::FAcquireActionsToPropertiesTask::FAcquireActionsToPropertiesTask(
        const TSharedPtr<FFormDomain> Self,
        const Request::FAcquireActionsToFormPropertiesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FAcquireActionsToPropertiesTask::FAcquireActionsToPropertiesTask(
        const FAcquireActionsToPropertiesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FAcquireActionsToPropertiesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->AcquireActionsToFormProperties(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto StampSheet = MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                Self->Gs2->Cache,
                Self->Gs2->JobQueueDomain,
                Self->Gs2->RestSession,
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId(),
                Self->Gs2->StampSheetConfiguration
            );
            const auto Future3 = StampSheet->Run();
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return MakeShared<Core::Model::FTransactionError<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>(
                    Future3->GetTask().Error()->GetErrors(),
                    [&]() -> TSharedPtr<FAsyncTask<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>
                    {
                        return MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                            Self->Gs2->Cache,
                            Self->Gs2->JobQueueDomain,
                            Self->Gs2->RestSession,
                            *ResultModel->GetStampSheet(),
                            *ResultModel->GetStampSheetEncryptionKeyId(),
                            Self->Gs2->StampSheetConfiguration
                        )->Run();
                    }
                );
            }
            Future3->EnsureCompletion();
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FAcquireActionsToPropertiesTask>> FFormDomain::AcquireActionsToProperties(
        Request::FAcquireActionsToFormPropertiesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireActionsToPropertiesTask>>(this->AsShared(), Request);
    }

    FFormDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFormDomain> Self,
        const Request::FDeleteFormByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->DeleteFormByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Delete(Gs2::Formation::Model::FForm::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Formation::Model::FMold::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Formation::Model::FMoldModel::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetFormModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MoldModelName,
                    "FormModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormModelDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Delete(Gs2::Formation::Model::FFormModel::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FDeleteTask>> FFormDomain::Delete(
        Request::FDeleteFormByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFormDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MoldModelName,
        TOptional<FString> Index,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MoldModelName.IsSet() ? *MoldModelName : "null") + ":" +
            (Index.IsSet() ? *Index : "null") + ":" +
            ChildType;
    }

    FString FFormDomain::CreateCacheKey(
        TOptional<FString> Index
    )
    {
        return FString("") +
            (Index.IsSet() ? *Index : "null");
    }

    FFormDomain::FModelTask::FModelTask(
        const TSharedPtr<FFormDomain> Self
    ): Self(Self)
    {

    }

    FFormDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FForm> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FForm>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetFormByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "form")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Formation::Model::FForm>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    Self->Index.IsSet() ? FString::FromInt(*Self->Index) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FModelTask>> FFormDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFormDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FFormDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FFormPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FForm::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                Index.IsSet() ? FString::FromInt(*Index) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FForm>(obj));
            }
        );
    }

    void FFormDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            ParentKey,
            Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                Index.IsSet() ? FString::FromInt(*Index) : TOptional<FString>()
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

