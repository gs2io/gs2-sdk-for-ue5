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

#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestModelDomain::FQuestModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName,
        const TOptional<FString> QuestName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Session)),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName),
        QuestName(QuestName),
        ParentKey(Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
            NamespaceName,
            QuestGroupName,
            "QuestModel"
        ))
    {
    }

    FQuestModelDomain::FQuestModelDomain(
        const FQuestModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        QuestGroupName(From.QuestGroupName),
        QuestName(From.QuestName),
        ParentKey(From.ParentKey)
    {

    }

    FQuestModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestModelDomain> Self,
        const Request::FGetQuestModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName)
            ->WithQuestName(Self->QuestName);
        const auto Future = Self->Client->GetQuestModel(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->QuestGroupName,
                    "QuestModel"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestModel::TypeName,
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

    TSharedPtr<FAsyncTask<FQuestModelDomain::FGetTask>> FQuestModelDomain::Get(
        Request::FGetQuestModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FQuestModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> QuestGroupName,
        TOptional<FString> QuestName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            (QuestName.IsSet() ? *QuestName : "null") + ":" +
            ChildType;
    }

    FString FQuestModelDomain::CreateCacheKey(
        TOptional<FString> QuestName
    )
    {
        return FString("") +
            (QuestName.IsSet() ? *QuestName : "null");
    }

    FQuestModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestModelDomain> Self
    ): Self(Self)
    {

    }

    FQuestModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Quest::Model::FQuestModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Quest::Model::FQuestModel>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                Self->QuestName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetQuestModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                    Self->QuestName
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "questModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Quest::Model::FQuestModel>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                    Self->QuestName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestModelDomain::FModelTask>> FQuestModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FQuestModelDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FQuestModelPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                QuestName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FQuestModel>(obj));
            }
        );
    }

    void FQuestModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Quest::Model::FQuestModel::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FQuestModelDomain::CreateCacheKey(
                QuestName
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

