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

#include "Core/Domain/SpeculativeExecutor/SpeculativeExecutor.h"

#include "Account/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Account/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "AdReward/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "AdReward/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Auth/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Auth/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Chat/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Chat/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Core/Domain/Gs2.h"
#include "Datastore/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Datastore/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Dictionary/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Dictionary/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Distributor/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Distributor/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Enchant/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Enchant/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Enhance/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Enhance/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Exchange/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Exchange/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Experience/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Experience/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Formation/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Formation/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Friend/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Friend/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Gateway/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Gateway/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Idle/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Idle/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Inbox/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Inbox/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Inventory/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Inventory/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "JobQueue/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "JobQueue/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Key/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Key/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Limit/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Limit/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Lock/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Lock/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "LoginReward/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "LoginReward/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Lottery/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Lottery/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Matchmaking/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Matchmaking/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "MegaField/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "MegaField/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Mission/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Mission/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Money/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Money/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "News/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "News/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Quest/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Quest/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Ranking/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Ranking/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Realtime/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Realtime/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Schedule/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Schedule/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "SerialKey/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "SerialKey/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Showcase/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Showcase/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "SkillTree/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "SkillTree/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Stamina/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Stamina/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "StateMachine/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "StateMachine/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Version/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Version/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    FSpeculativeExecutor::FSpeculativeExecutor(
    	const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
		const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireActions,
	    const double Rate
	):
		ConsumeActions(ConsumeActions),
		AcquireActions(AcquireActions),
		Rate(Rate)
    {
    }

    FSpeculativeExecutor::FSpeculativeExecutor(
    	const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
	    const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireActions,
	    const TBigInt<1024, false>& Rate
    ):
		ConsumeActions(ConsumeActions),
		AcquireActions(AcquireActions),
		Rate(Rate)
    {
    }

    FSpeculativeExecutor::FCommitTask::FCommitTask(
    	const Gs2::Core::Domain::FGs2Ptr& Domain,
    	const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
		const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& ConsumeActions,
		const TSharedPtr<TArray<Gs2::Core::Model::FAcquireActionPtr>>& AcquireActions,
	    const TBigInt<1024, false>& Rate
	):
	    Domain(Domain),
	    AccessToken(AccessToken),
		ConsumeActions(ConsumeActions),
		AcquireActions(AcquireActions),
	    Rate(Rate)
    {
    }

    FSpeculativeExecutor::FCommitTask::FCommitTask(
	    const FCommitTask& From
	):
		Domain(From.Domain),
		AccessToken(From.AccessToken),
		ConsumeActions(From.ConsumeActions),
		AcquireActions(From.AcquireActions),
		Rate(From.Rate)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSpeculativeExecutor::FCommitTask::Action(
	    TSharedPtr<TSharedPtr<TFunction<void()>>> Result
	)
    {
    	const auto Commit = new TArray<TSharedPtr<TFunction<void()>>>();
    	if (ConsumeActions.IsValid())
    	{
    		for (auto ConsumeAction : *ConsumeActions)
    		{
    			{
				    const auto Future = Gs2::Account::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
					    Domain,
					    Domain->Account,
					    AccessToken,
					    ConsumeAction,
					    Rate
				    );
				    Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::AdReward::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->AdReward,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Auth::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Auth,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Chat::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Chat,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Datastore::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Datastore,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Dictionary::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Dictionary,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Distributor::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Distributor,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Enchant::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Enchant,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Enhance::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Enhance,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Exchange::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Exchange,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Experience::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Experience,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Formation::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Formation,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Friend::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Friend,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Gateway::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Gateway,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Idle::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Idle,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Inbox::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Inbox,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Inventory::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Inventory,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::JobQueue::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->JobQueue,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Key::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Key,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Limit::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Limit,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Lock::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Lock,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::LoginReward::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->LoginReward,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Lottery::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Lottery,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Matchmaking::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Matchmaking,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::MegaField::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->MegaField,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Mission::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Mission,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Money::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Money,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::News::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->News,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Quest::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Quest,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Ranking::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Ranking,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Realtime::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Realtime,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Schedule::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Schedule,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::SerialKey::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->SerialKey,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Showcase::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Showcase,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::SkillTree::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->SkillTree,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Stamina::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Stamina,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::StateMachine::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->StateMachine,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Version::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Version,
						AccessToken,
						ConsumeAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    		}
    	}
    	if (AcquireActions.IsValid())
    	{
    		for (auto AcquireAction : *AcquireActions)
    		{
    			{
    				const auto Future = Gs2::Account::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Account,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::AdReward::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->AdReward,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Auth::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Auth,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Chat::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Chat,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Datastore::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Datastore,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Dictionary::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Dictionary,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Distributor::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Distributor,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Enchant::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Enchant,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Enhance::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Enhance,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Exchange::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Exchange,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Experience::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Experience,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Formation::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Formation,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Friend::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Friend,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Gateway::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Gateway,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Idle::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Idle,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Inbox::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Inbox,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Inventory::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Inventory,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::JobQueue::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->JobQueue,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Key::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Key,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Limit::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Limit,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Lock::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Lock,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::LoginReward::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->LoginReward,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Lottery::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Lottery,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Matchmaking::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Matchmaking,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::MegaField::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->MegaField,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Mission::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Mission,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Money::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Money,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::News::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->News,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Quest::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Quest,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Ranking::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Ranking,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Realtime::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Realtime,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Schedule::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Schedule,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::SerialKey::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->SerialKey,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Showcase::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Showcase,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::SkillTree::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->SkillTree,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Stamina::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Stamina,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::StateMachine::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->StateMachine,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    			{
    				const auto Future = Gs2::Version::Domain::SpeculativeExecutor::FAcquireActionSpeculativeExecutorIndex::Execute(
						Domain,
						Domain->Version,
						AccessToken,
						AcquireAction,
						Rate
					);
    				Future->StartSynchronousTask();
    				if (Future->GetTask().IsError())
    				{
    					return Future->GetTask().Error();
    				}
    				Commit->Add(Future->GetTask().Result());
    			}
    		}
    	}
    	*Result = MakeShared<TFunction<void()>>([&]
		{
			for (auto C : *Commit)
			{
				if (C.IsValid())
				{
					(*C)();
				}
			}
		});
	    return nullptr;
    }

    TSharedPtr<FAsyncTask<FSpeculativeExecutor::FCommitTask>> FSpeculativeExecutor::Execute(
	    const Gs2::Core::Domain::FGs2Ptr& Domain,
	    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
	)
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, AccessToken, ConsumeActions, AcquireActions, Rate);
    }
}
