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

#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FCompletedQuestListAccessTokenDomain::FCompletedQuestListAccessTokenDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> QuestGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        QuestGroupName(QuestGroupName),
        ParentKey(Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "CompletedQuestList"
        ))
    {
    }

    FCompletedQuestListAccessTokenDomain::FCompletedQuestListAccessTokenDomain(
        const FCompletedQuestListAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        QuestGroupName(From.QuestGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FCompletedQuestListAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FCompletedQuestListAccessTokenDomain> Self,
        const Request::FGetCompletedQuestListRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCompletedQuestListAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCompletedQuestListAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCompletedQuestList>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->GetCompletedQuestList(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "CompletedQuestList"
                );
                const auto Key = Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetQuestGroupName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FCompletedQuestList::TypeName,
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

    TSharedPtr<FAsyncTask<FCompletedQuestListAccessTokenDomain::FGetTask>> FCompletedQuestListAccessTokenDomain::Get(
        Request::FGetCompletedQuestListRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FCompletedQuestListAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> QuestGroupName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            ChildType;
    }

    FString FCompletedQuestListAccessTokenDomain::CreateCacheKey(
        TOptional<FString> QuestGroupName
    )
    {
        return FString("") +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null");
    }

    FCompletedQuestListAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FCompletedQuestListAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FCompletedQuestListAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCompletedQuestListAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCompletedQuestList>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Quest::Model::FCompletedQuestList> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FCompletedQuestList>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                Self->QuestGroupName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetCompletedQuestListRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    Self->QuestGroupName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Quest::Model::FCompletedQuestList::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "completedQuestList")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Quest::Model::FCompletedQuestList>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                    Self->QuestGroupName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompletedQuestListAccessTokenDomain::FModelTask>> FCompletedQuestListAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCompletedQuestListAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCompletedQuestListAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Quest::Model::FCompletedQuestListPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                QuestGroupName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Quest::Model::FCompletedQuestList>(obj));
            }
        );
    }

    void FCompletedQuestListAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Quest::Model::FCompletedQuestList::TypeName,
            ParentKey,
            Gs2::Quest::Domain::Model::FCompletedQuestListDomain::CreateCacheKey(
                QuestGroupName
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

